
export const wait = async (ms: number) => new Promise(resolve => setTimeout(resolve, ms))
export const randomNumber = (min: number, max: number) => Math.floor(Math.random() * (max - min) + min)
