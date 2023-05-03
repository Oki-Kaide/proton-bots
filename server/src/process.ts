import { Api, JsonRpc, JsSignatureProvider } from '@protonprotocol/protonjs'
import fetch from 'node-fetch'
import { ENDPOINTS, PRIVATE_KEYS, BOTS_CONTRACT, BOTS_ACCOUNTS, ACTIONS_MULTIPLIER } from './constants'
import { wait, randomNumber } from './utils'
import { fetchPrices } from './price'

const apis = ENDPOINTS.map((_) => {
    const rpc = new JsonRpc(ENDPOINTS, { fetch: fetch })
    const api = new Api({ rpc, signatureProvider: new JsSignatureProvider(PRIVATE_KEYS as any) })
    return {
        rpc,
        api
    }
})

const process = async (account: BotAccount, index: number = 1) => {
    const prices = await fetchPrices()

    const actions = []

    for (let i = 0; i < ACTIONS_MULTIPLIER; i++) {
        if (prices[account.oracle.baseId] === undefined || prices[account.oracle.baseId][account.oracle.quoteId] === undefined || prices[account.oracle.baseId][account.oracle.quoteId] <= 0) {
            console.error('Not configured for price: ', account)
        } 

        const price = prices[account.oracle.baseId][account.oracle.quoteId]

        actions.push({
            account: BOTS_CONTRACT,
            name: 'process',
            data: {
                account: account.name,
                entries: [{
                    bot_index: account.bot_index,
                    data: {
                        d_double: price,
                        d_string: null,
                        d_uint64_t: null
                    }
                }],
                oracle_index: account.oracle.oracle_index,
                nonce: randomNumber(1, 200000)
            } as Process,
            authorization: [ { actor: account.name, permission: account.permission } ]
        })
    }

    try {
        const { api } = apis[index % apis.length]
        const result = await api.transact({
            actions
        }, {
            useLastIrreversible: true,
            expireSeconds: 400
        })
        return result
    } catch (e) {
        console.log(e)
    }
}

const processor = async (account: BotAccount) => {
    const toProcess = Array(account.parallel).fill(0)
    await Promise.all(
        toProcess.map((_, i) => process(account, i))
    )

    await wait(account.timer)
    processor(account)
}

export const main = () => {
    for (const account of BOTS_ACCOUNTS) {
        processor(account)
    }
}