#
# listen to trades on bitstamp via websockets
import asyncio
import websockets
import json
import argparse

address = "wss://api2.poloniex.com"

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

    subscription = {"command": "subscribe", "channel": 1002}
    print("running polo listener on subscription {}".format(json.dumps(subscription)))
    asyncio.get_event_loop().run_until_complete(listener(subscription))

        
