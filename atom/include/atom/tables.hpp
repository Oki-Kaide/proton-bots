#pragma once

namespace proton {
  struct data_variant {
    std::optional<std::string> d_string;
    std::optional<uint64_t> d_uint64_t;
    std::optional<double> d_double;

    data_variant () {};
    data_variant (std::string val) { d_string = val; };
    data_variant (uint64_t val) { d_uint64_t = val; };
    data_variant (double val) { d_double = val; };
    
    bool operator < ( const data_variant& rhs ) const { return true; }
    bool operator > ( const data_variant& rhs ) const { return true; }

    std::string data_type ()const {
      if (d_string.has_value()) {
        return "string";
      } else if (d_uint64_t.has_value()) {
        return "uint64_t";
      } else if (d_double.has_value()) {
        return "double";
      } else {
        eosio::check(false, "invalid data_variant type");
        return {};
      }
    };

    template<typename T>
    T get ()const {
      std::string data_type = this->data_type();
      if constexpr (std::is_same<T, std::string>::value && data_type == "string") {
        return *d_string;
      } else if (std::is_same<T, uint64_t>::value && data_type == "uint64_t") {
        return *d_uint64_t;
      } else if (std::is_same<T, double>::value && data_type == "double") {
        return *d_double;
      } else {
        eosio::check(false, "invalid data_variant get");
        return {};
      }
    };

    EOSLIB_SERIALIZE( data_variant, (d_string)(d_uint64_t)(d_double) )
  };

  struct BotEntry {
    uint64_t bot_index;
    data_variant data;

    EOSLIB_SERIALIZE ( BotEntry, (bot_index)(data) )
  };

  struct OracleEntry {
    uint64_t oracle_index;
    data_variant data;

    EOSLIB_SERIALIZE ( OracleEntry, (oracle_index)(data) )
  };

  static inline eosio::checksum256 get_txid () {
    auto size = eosio::transaction_size();
    char buf[size];
    uint32_t read = eosio::read_transaction(buf, size);
    eosio::check( size == read, "read_transaction failed");
    return eosio::sha256(buf, size);
  }

  struct Tx {
    eosio::checksum256 id;
    eosio::time_point time;
    data_variant data;

    EOSLIB_SERIALIZE ( Tx, (id)(time)(data) )
  };

  struct [[eosio::table, eosio::contract("atom")]] Bot {
    uint64_t index;
    eosio::name account;
    std::string description;
    eosio::name oracle_contract;
    uint64_t feed_index;
    std::map<uint8_t, uint64_t> tx_count_by_utc_hour;
    uint8_t max_history;
    std::vector<Tx> history;

    uint64_t primary_key() const { return index; };

    EOSLIB_SERIALIZE ( Bot, (index)(account)(description)
                            (oracle_contract)(feed_index)
                            (tx_count_by_utc_hour)(max_history)(history) )
  };
  typedef eosio::multi_index<"bots"_n, Bot> bots_table;
}