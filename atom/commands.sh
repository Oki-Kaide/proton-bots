cleosp push action bot cleanup '[]' -p bot 

cleosp set contract bot atom 

cleosp push action bot addbot '{
        "bot": {
                "index": 0,
                "account": "bot1",
                "description": "XPR/BTC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 0,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 1,
                "account": "bot2",
                "description": "XPR/BTC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 0,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 2,
                "account": "bot3",
                "description": "XPR/BTC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 0,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 3,
                "account": "bot4",
                "description": "XPR/BTC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 0,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 4,
                "account": "bot1",
                "description": "BTC/USDC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 1,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 5,
                "account": "bot2",
                "description": "BTC/USDC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 1,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 6,
                "account": "bot3",
                "description": "BTC/USDC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 1,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot addbot '{
        "bot": {
                "index": 7,
                "account": "bot4",
                "description": "BTC/USDC Oracle Feed",
                "oracle_contract": "oracles",
                "feed_index": 1,
                "tx_count_by_utc_hour": [],
                "max_history": 20,
                "history": []
        }
}' -p bot;

cleosp push action bot process '{
        "account": "bot",
        "bot_index": 0,
        "data": ["float64", 0.00000045]
}' -p bot;
