import json
import os
import sys
import logging
import urllib.request
import openai

from linebot import LineBotApi, WebhookHandler
from linebot.models import MessageEvent, TextMessage, TextSendMessage
from linebot.exceptions import LineBotApiError, InvalidSignatureError

# ERROR以上のログメッセージを拾うように設定する
logger = logging.getLogger()
# logger.setLevel(logging.ERROR)
# 受け取ったWebhookのJSONを目視確認したいときは、INFO以上のログメッセージを拾うようにする
logger.setLevel(logging.INFO)

# 環境変数からチャネルアクセストークンとチャネルシークレットを取得する
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')
REPLY_URL = 'https://api.line.me/v2/bot/message/reply'
# OpenAI APIキーの設定
openai.api_key = os.getenv('SECRET_KEY')
API_ENDPOINT = 'https://api.openai.com/v1/engine/davinci-codex/completions'

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

response = {
    'statusCode': 200,
    'body': json.dumps('Hello from Lambda!')
}

error_response = {
    'statusCode': 500,
    'body': json.dumps('Only webhooks from the LINE Platform will be accepted.')
}

# LINE Messaging APIのWebhookからのリクエストを処理する


def lambda_handler(event, context):

    # リクエストヘッダーにx-line-signatureがあることを確認
    if "x-line-signature" in event['headers']:
        signature = event['headers']['x-line-signature']

    body = event['body']
    # 受け取ったWebhookのJSONを目視確認できるようにINFOでログに吐く
    logger.info(body)

    # ChatGPTに質問を投げて回答を取得する
    # question = event.message.text
    # response = openai.Completion.create(
    #    engine='davinci', prompt=question, max_tokens=1024, n=1, stop=None, temperature=0.5)
    # answer = response.choices[0].text.strip()
    # logger.info(answer)

    # オウム返しする処理
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
