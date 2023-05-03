#pragma once

// Standard.
#include <vector>

// EOS
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>
#include <eosio/transaction.hpp>

// Local
#include "tables.hpp"

namespace proton {
  CONTRACT atom : public eosio::contract {
  public:
    using contract::contract;

    atom( eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds )
      : contract(receiver, code, ds),
        _bots(receiver, receiver.value) {}

    ACTION addbot    ( const Bot& bot            );
    ACTION updatebot ( const Bot& bot            );
    ACTION removebot ( const uint64_t& bot_index );
    ACTION process   (
      const eosio::name& account,
      const std::vector<BotEntry>& entries,
      const uint64_t& nonce,
      const uint64_t& oracle_index
    );

    ACTION cleanup () {
      require_auth(get_self());
      
      bots_table db(get_self(), get_self().value);
      auto itr = db.end();
      while(db.begin() != itr){
        itr = db.erase(--itr);
      }
    }

    // External oracle contract
    void feed (
      const eosio::name& account,
      const uint64_t& feed_index,
      const data_variant& data
    );
    using feed_action = eosio::action_wrapper<"feed"_n, &atom::feed>;

    // Initialize tables from tables.hpp
    bots_table _bots;

  private:

  };
}