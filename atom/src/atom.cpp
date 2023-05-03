#include <atom/atom.hpp>

namespace proton
{
  void atom::addbot (const Bot& bot) {
    require_auth(get_self());

    auto bot_itr = _bots.find(bot.index);
    eosio::check(bot_itr == _bots.end(), "bot already exists");
    _bots.emplace(get_self(), [&](auto& p) {
      p = bot;
    });
  }

  void atom::updatebot (const Bot& bot) {
    require_auth(get_self());

    auto bot_itr = _bots.require_find(bot.index, "bot does not exist");
    _bots.modify(bot_itr, get_self(), [&](auto& p) {
      p = bot;
    });
  }

  void atom::removebot (const uint64_t& bot_index) {
    require_auth(get_self());

    auto bot = _bots.require_find(bot_index, "bot not found");
    _bots.erase(bot);
  }

  // Multiple bots entering data for 1 oracle
  void atom::process (
    const eosio::name& account,
    const std::vector<BotEntry>& entries,
    const uint64_t& nonce,
    const uint64_t& oracle_index
  ) {
    for (const auto& entry: entries) {
      // Find bot
      auto bot = _bots.require_find(entry.bot_index, "bot not found");
      eosio::check(account == bot->account, "account mismatch");
      
      // Send oracle
      feed_action f_action( bot->oracle_contract, {account, "active"_n} );
      f_action.send(account, oracle_index, entry.data);

      // Save stats
      auto current_time_point = eosio::current_time_point();
      auto utc_hour = (current_time_point.sec_since_epoch() % 86400) / 3600;
      auto utc_hour_to_erase = (utc_hour + 1) % 24;
      _bots.modify(bot, get_self(), [&](auto& b) {
        b.tx_count_by_utc_hour[utc_hour]++;
        b.tx_count_by_utc_hour[utc_hour_to_erase] = 0;
        
        b.history.insert(b.history.begin(), { get_txid(), current_time_point, entry.data });
        if (b.history.size() > b.max_history) {
          b.history.pop_back();
        }
      });
    }
  }

  // Multiple oracle entries by 1 bot
  void atom::process2 (
    const eosio::name& account,
    const std::vector<OracleEntry>& entries,
    const uint64_t& nonce,
    const uint64_t& bot_index
  ) {
    // Auth
    require_auth(account);
    
    // Find bot
    auto bot = _bots.require_find(bot_index, "bot not found");
    eosio::check(account == bot->account, "account mismatch");
    
    for (const auto& entry: entries) {
      // Send oracle
      feed_action f_action(bot->oracle_contract, {account, "active"_n} );
      f_action.send(account, entry.oracle_index, entry.data);

      // Save stats
      auto current_time_point = eosio::current_time_point();
      auto utc_hour = (current_time_point.sec_since_epoch() % 86400) / 3600;
      auto utc_hour_to_erase = (utc_hour + 1) % 24;
      _bots.modify(bot, get_self(), [&](auto& b) {
        b.tx_count_by_utc_hour[utc_hour]++;
        b.tx_count_by_utc_hour[utc_hour_to_erase] = 0;
        
        b.history.insert(b.history.begin(), { get_txid(), current_time_point, entry.data });
        if (b.history.size() > b.max_history) {
          b.history.pop_back();
        }
      });
    }
  }
} // namepsace contract