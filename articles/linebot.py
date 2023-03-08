import json
import os
import urllib.request


def lambda_handler(event, context):
    # 環境変数のチャネルアクセストークンを取得
    token = os.environ['CHANNEL_ACCESS_TOKEN']
    reply_url = 'https://api.line.me/v2/bot/message/reply'

    # json.loadsの

    for message_event in json.loads(event['body'])['events']:
        headers = {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + token
        }
        body = {
            'replyToken': message_event['replyToken'],
            'messages':
            [
                {
                    "type": "flex",
                    "altText": "This is a Flex Message",
                    "contents": {
                        "type": "bubble",
                        "hero": {
                            "type": "image",
                            "url": "https://pbs.twimg.com/profile_images/1041212484/100630_170522_400x400.jpg",
                            "size": "full",
                            "aspectRatio": "20:13",
                            "aspectMode": "cover"
                        },
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "text",
                                    "text": message_event['message']['text'] + 'にゃん',
                                    "weight": "bold",
                                    "size": "xl"
                                }
                            ]
                        }
                    }
                }
            ]
        }

        req = urllib.request.Request(reply_url, data=json.dumps(
            body).encode('utf-8'), method='POST', headers=headers)
        with urllib.request.urlopen(req) as res:
            logger.info(res.read().decode("utf-8"))

    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
