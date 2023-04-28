curl -v -X POST https://api.line.me/v2/bot/message/broadcast \
-H 'Content-Type: application/json' \
-H 'Authorization: Bearer {チャネルアクセストークン}' \
-d '{
    "messages":[
        {
            "type":"text",
            "text":"Messaging APIでメッセージを送信しています。"
        },
        {
            "type": "sticker",
            "packageId": "6325",
            "stickerId": "10979905"
        }
    ]
}'
