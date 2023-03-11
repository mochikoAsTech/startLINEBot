import json
import os
import sys
import logging
import urllib.request

from linebot import (
    LineBotApi, WebhookHandler
)
from linebot.models import (
    MessageEvent, TextMessage, TextSendMessage,
)
from linebot.exceptions import (
    LineBotApiError, InvalidSignatureError
)

# WARNING, ERROR, CRITICALのログメッセージを拾うように設定する
logger = logging.getLogger()
logger.setLevel(logging.WARNING)

# 環境変数からチャネルアクセストークンとチャネルシークレットを取得する
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')
REPLY_URL = 'https://api.line.me/v2/bot/message/reply'

# チャネルアクセストークンとチャネルシークレットが環境変数に登録されていないとエラー
if CHANNEL_SECRET is None:
    logger.error(
        'LINE_CHANNEL_SECRET is not defined as environmental variables.')
    sys.exit(1)
if CHANNEL_ACCESS_TOKEN is None:
    logger.error(
        'LINE_CHANNEL_ACCESS_TOKEN is not defined as environmental variables.')
    sys.exit(1)


def lambda_handler(event, context):
    for message_event in json.loads(event['body'])['events']:
        headers = {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + CHANNEL_ACCESS_TOKEN
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

        req = urllib.request.Request(REPLY_URL, data=json.dumps(
            body).encode('utf-8'), method='POST', headers=headers)
        with urllib.request.urlopen(req) as res:
            logger.info(res.read().decode("utf-8"))

    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
