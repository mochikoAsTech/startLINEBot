import json
import logging
import openai
import os
import sys

from linebot import LineBotApi, WebhookHandler
from linebot.exceptions import InvalidSignatureError, LineBotApiError
from linebot.models import MessageEvent, TextMessage, TextSendMessage

# ERROR以上のログメッセージを拾うように設定する
logger = logging.getLogger()
# logger.setLevel(logging.ERROR)
# 受け取ったWebhookのJSONを目視確認したいときは、INFO以上のログメッセージを拾うようにする
logger.setLevel(logging.INFO)

# 環境変数からチャネルアクセストークンとチャネルシークレットを取得する
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')

# OpenAI APIキーの設定
openai.api_key = os.getenv('SECRET_KEY')

# チャネルアクセストークンとチャネルシークレットとOpen APIキーが環境変数に登録されていないとエラー
if CHANNEL_SECRET is None:
    logger.error(
        'LINE_CHANNEL_SECRET is not defined as environmental variables.')
    sys.exit(1)
if CHANNEL_ACCESS_TOKEN is None:
    logger.error(
        'LINE_CHANNEL_ACCESS_TOKEN is not defined as environmental variables.')
    sys.exit(1)
if openai.api_key is None:
    logger.error('Open API key is not defined as environmental variables.')
    sys.exit(1)

line_bot_api = LineBotApi(CHANNEL_ACCESS_TOKEN)
webhook_handler = WebhookHandler(CHANNEL_SECRET)

# オウム返しをする処理
@webhook_handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    # 応答トークンを使って応答メッセージを送る
    line_bot_api.reply_message(
        event.reply_token, TextSendMessage(text=event.message.text))

# LINE Messaging APIからのWebhookを処理する
def lambda_handler(event, context):

    # リクエストヘッダーにx-line-signatureがあることを確認
    if 'x-line-signature' in event['headers']:
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

    try:
        webhook_handler.handle(body, signature)
    except InvalidSignatureError:
        # 署名を検証した結果、飛んできたのがLINEプラットフォームからのWebhookでなければ400を返す
        return {
            'statusCode': 400,
            'body': json.dumps('Only webhooks from the LINE Platform will be accepted.')
        }
    except LineBotApiError as e:
        # 応答メッセージを送ろうとしたがLINEプラットフォームからエラーが返ってきたらエラーを吐く
        logger.error('Got exception from LINE Messaging API: %s\n' % e.message)
        for m in e.error.details:
            logger.error('  %s: %s' % (m.property, m.message))

    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
