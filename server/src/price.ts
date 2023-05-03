import fetch from 'node-fetch'
import { ORACLES, PRICE_FETCH_TIMER } from './constants'
import throttle from 'lodash.throttle'

const baseIds = ORACLES.map(oracle => oracle.baseId)
const quoteCurrencies = ORACLES.map(oracle => oracle.quoteCurrency)

export const fetchPrices = throttle(async () => {
    const res = await fetch(`https://api.coingecko.com/api/v3/simple/price?ids=${baseIds.join(',')}&vs_currencies=${quoteCurrencies.join(',')}`)
    const json = await res.json()
    return json
}, PRICE_FETCH_TIMER)