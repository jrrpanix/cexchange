#
# listen to trades on bitstamp via websockets
import asyncio
import websockets
import json
import argparse

address = 'wss://ws-feed.gdax.com' 
#address = 'wss://ws-feed-public.sandbox.pro.coinbase.com' # for testing

sub0 = {
    "type": "subscribe",
    "product_ids": [
        "BTC-USD"
    ],
    "channels": [
        "level2",
        "heartbeat",
        {
            "name": "ticker",
            "product_ids": [
                "BTC-USD"
            ]
        }
    ]
}

sub = {
    "type": "subscribe",
    "product_ids": [
        "BTC-USD"
    ],
    "channels": [
        "heartbeat",
        {
            "name": "ticker",
            "product_ids": [
                "BTC-USD"
            ]
        }
    ]
}


async def listener(subscription):
    async with websockets.connect(address) as websocket:
        print("connected")
        await websocket.send(json.dumps(subscription))
        while True:
            try:
                response = await websocket.recv()
                print(response)
            except:
                print("Error Found")
                quit()
                

if __name__ == '__main__':

    asyncio.get_event_loop().run_until_complete(listener(sub))

        
