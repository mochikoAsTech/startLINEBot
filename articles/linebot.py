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

# ERROR以上のログメッセージを拾うように設定する
logger = logging.getLogger()
logger.setLevel(logging.ERROR)
# 受け取ったWebhookのJSONを目視確認したいときは、INFO以上のログメッセージを拾うようにする
# logger.setLevel(logging.INFO)

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

line_bot_api = LineBotApi(CHANNEL_ACCESS_TOKEN)
handler = WebhookHandler(CHANNEL_SECRET)


def lambda_handler(event, context):

    # リクエストヘッダーにx-line-signatureがあることを確認
    if "x-line-signature" in event['headers']:
        signature = event['headers']['x-line-signature']

    body = event["body"]
    # 受け取ったWebhookのJSONを目視確認できるようにINFOでログに吐く
    logger.info(body)

    response = {
        "isBase64Encoded": false,
        "statusCode": 200,
        "body": "{ \"message\": \"Hello from Lambda!\" }",
        "headers": {
            "content-type": "application/json"
        }
    }
    error_response = {"isBase64Encoded": False,
                      "statusCode": 404,
                      "headers": {},
                      "body": "Error"}

    @handler.add(MessageEvent, message=TextMessage)
    def handle_message(event):
        # 応答トークンを使って応答メッセージを送る
        line_bot_api.reply_message(
            event.reply_token, TextSendMessage(text=event.message.text))

    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        # 署名を検証した結果、飛んできたのがLINEプラットフォームからのWebhookでなければ500を返す
        return error_response
    except LineBotApiError as e:
        # 応答メッセージを送ろうとしたがLINEプラットフォームからエラーが返ってきたらエラーを吐く
        logger.ERROR("Got exception from LINE Messaging API: %s\n" % e.message)
        for m in e.error.details:
            logger.ERROR("  %s: %s" % (m.property, m.message))
        return error_response

    return response


#    return {
#        'statusCode': 200,
#        'body': json.dumps('Hello from Lambda!')
#    }
