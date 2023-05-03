interface BotAccount {
    bot_index: number;
    name: string;
    permission: string;
    timer: number;
    parallel: number;
    oracle: Oracle
}

interface Data {
    d_string: string | null;
    d_uint64_t: number | null;
    d_double: number | null;
}

interface OracleEntry {
    oracle_index: number;
    data: Data;
}

interface BotEntry {
    bot_index: number;
    data: Data;
}
interface Process {
    account: string;
    entries: BotEntry[];
    nonce: number;
    oracle_index: number;
}
interface Process2 {
    account: string;
    entries: OracleEntry[];
    nonce: number;
    bot_index: number;
}

interface Oracle {
    oracle_index: number;
    baseCurrency: string;
    baseId: string;
    quoteCurrency: string;
    quoteId: string;
}