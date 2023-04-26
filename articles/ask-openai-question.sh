curl https://api.openai.com/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer シークレットキー" \
  -d '{
    "model": "gpt-3.5-turbo",
    "messages": [{"role": "user", "content": "技術書典ってなんですか？"}]
  }'
