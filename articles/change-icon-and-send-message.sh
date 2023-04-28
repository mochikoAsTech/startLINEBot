curl -v -X POST https://api.line.me/v2/bot/message/broadcast \
-H 'Content-Type: application/json' \
-H 'Authorization: Bearer {チャネルアクセストークン}' \
-d '{
    "messages": [
        {
            "type": "text",
            "text": "こんにちは。今日は原稿で忙しいにんげんの代わりに、ねこがメッセージをお届けします。",
            "sender": {
                "name": "ねこ",
                "iconUrl": "https://pbs.twimg.com/media/FueHfQNaYAEgNUj?format=jpg&name=900x900"
            }
        },
        {
            "type": "text",
            "text": "あ、ねこ！勝手にメッセージ送っちゃだめだよ！"
        }
    ]
}'
