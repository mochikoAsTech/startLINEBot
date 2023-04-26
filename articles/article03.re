= Messaging APIの色んな機能を試してみよう

色んな機能を組み合わせて自分だけのLINE Botをつくってみよう！

//pagebreak

== メッセージ送信に関する機能

LINE公式アカウントからメッセージを送るとき、普通に送るだけでなく、特定の人や属性を指定して送ったり、見た目にこだわったメッセージを送ったりすることができます。

=== ユーザーIDを指定して特定の人に送る

Messaging APIでメッセージを送るとき、いちばん簡単なのは友だち全員にメッセージを一斉配信するブロードキャストメッセージです。ですがユーザーIDを指定して、特定の人にだけメッセージを送ることも可能です。特定のひとりにだけ送りたいときはプッシュメッセージ、特定の数人にまとめて送りたいときはマルチキャストメッセージで送れます。

友だちのユーザーIDは、LINEプラットフォームから飛んでくるWebhookの@<ttb>{source}オブジェクトに含まれています。@<fn>{user-ids}

//footnote[user-ids][ユーザーIDを取得する | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/getting-user-ids/}]

===[column] 【コラム】開発チームだけにメッセージのテスト配信がしたい
     
たとえば本番用のLINE公式アカウントと、テスト用のLINE公式アカウントを別々に用意しておいて、開発チームのメンバーだけがテスト用のLINE公式アカウントと友だちになることで、本番配信前のメッセージのテスト配信と確認を実現していたとします。

この場合、開発チームに所属していたメンバーがAさん、Bさん、Cさんの中でCさんが退職してしまうと、残ったAさん、Bさん側でCさんをテスト用のLINE公式アカウントの友だちからブロックする方法がありません。退職前にCさんに頼んで、Cさん側からテスト用のLINE公式アカウントをブロックしてもらうしかないのです。

さらに厳密に言うと、一度Aさん、Bさんの目の前でCさんにブロックの操作をしてもらったとしても、Cさんの操作でブロックは解除できるので、悪意のあるCさんが後日ブロックを解除してしまうことはとめられません。こうなると、退職したCさんにも、発売前の商品や未発表の情報を含むテスト配信のメッセージが届き続けてしまいます。

なのでメッセージのテスト配信の仕組みは、「一度友だち追加されたら、開発者側からは友だち状態はコントロールできない」という前提で組んでおく必要があります。

たとえば、テスト配信のメッセージはテスト用のLINE公式アカウントから送るとしても、ブロードキャストメッセージで友だち全員に送るのではなく、開発チームのAさん、Bさん、CさんのユーザーIDを指定したマルチキャストメッセージを送る、という方法がお勧めです。これならCさんの退職後、開発チームに残ったAさんBさんがマルチキャストメッセージの送信対象からCさんのユーザーIDを消せば、Cさんには公開前のテストメッセージは届かなくなります。

===[/column]

=== メッセージの配信対象を属性で絞り込む

ナローキャストメッセージを使うと、性別や年齢、地域、友だちになってからの期間といった属性情報を指定してメッセージを送ることが可能です。ただし属性情報を指定したメッセージ送信には、LINE公式アカウントのターゲットリーチが100人以上で、かつ属性情報を指定して絞り込んだ送信対象も50人以上であること、という制限事項があります。そもそも友だちが少なかったり、条件を絞り込みすぎて送信対象者が少なかったりすると、属性情報を指定したメッセージ送信はできませんので注意してください。@<fn>{limit}

//footnote[limit][属性情報やオーディエンスを利用したメッセージ送信の制限事項 | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#send-narrowcast-message-restrictions}]

たとえばブロードキャストメッセージで新商品予告のメッセージを全員に送って、そのメッセージのURLを開いたユーザーを「新商品に興味のあるオーディエンス」に入れておき、新商品の発売当日はそのオーディエンスだけを対象にして店頭イベントの告知を送る、というようなこともできます。@<fn>{audience}

//footnote[audience][属性情報やリターゲティングを利用して複数のユーザーに送信する（ナローキャストメッセージ） | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/sending-messages/#send-narrowcast-message}]

=== メッセージ送信元のアイコンと表示名を変更する

メッセージを送るときに、送信元のアイコンと表示名を変更して送ることができます。@<fn>{nickname}

//footnote[nickname][アイコンおよび表示名を変更する | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/icon-nickname-switch/}]

次のcurlコマンド@<fn>{change-icon-and-send-message}（@<list>{send-message-from-cat}）をたたくと、LINE公式アカウントからこんなメッセージが届きます。（@<img>{change-icon-and-name}）

//footnote[change-icon-and-send-message][このコードはGitHubで公開されている本書のリポジトリからもダウンロードできます。 @<href>{https://github.com/mochikoAsTech/startLINEBot/blob/master/articles/change-icon-and-send-message.sh}]

//listnum[send-message-from-cat][アイコンや表示名を変更してメッセージを送るcurlコマンド][sh]{
curl -v -X POST https://api.line.me/v2/bot/message/broadcast \
-H 'Content-Type: application/json' \
-H 'Authorization: Bearer チャネルアクセストークン' \
-d '{
    "messages": [
        {
            "type": "text",
            "text": "こんにちは。今日は原稿で忙しいにんげんの代わりに、ねこがメッセージをお届けします。",
            "sender": {
                "name": "ねこ",
                "iconUrl": "https://pbs.twimg.com/media/FueHfQNaYAEgNUj?format@<embed>$|latex|\linebreak\hspace*{0ex}$=jpg&name=900x900"
            }
        },
        {
            "type": "text",
            "text": "あ、ねこ！勝手にメッセージ送っちゃだめだよ！"
        }
    ]
}'
//}

//image[change-icon-and-name][ねこからメッセージが届いた][scale=0.6]{
//}

たとえばテーマパークのLINE公式アカウントで、特定のキャラクターにちなんだイベントを告知するときだけ、メッセージの送信元をそのキャラクターのアイコンと名前にする、といった使い方が可能です。

===[column] 【コラム】URLを送る前にOGPの見た目を確認したり、キャッシュを消したりしたい

LINEでURLを含むメッセージを送ると、こんなふうにプレビューが表示されます。（@<img>{url-preview}）

//image[url-preview][URLのプレビュー][scale=0.4]{
//}

実際にメッセージを送る前に、このプレビューでどんな画像やテキストが表示されるのか、確認したかったらどうすればいいのでしょう？

PagePokerという公式のツールを使うと、対象ページのOGPタグ@<fn>{ogp}を読み込んで、どんなふうにプレビューが表示されるのかを事前に確認できます。@<fn>{card-validator}

 * PagePoker
 ** @<href>{https://poker.line.naver.jp/}

［Clear Cache］にチェックを入れることで、文字通りLINE側サーバーのキャッシュをクリアできるようです。ページのOGP画像を差し替えたら、ここで先にキャッシュをクリアしてからそのページのURLを含むメッセージを送るようにすることで、「OGP画像を差し替えたのになぜか古い画像がプレビューで表示されてしまった」という事態は避けられそうです。OGPタグの書き方については、LINE DevelopersサイトのFAQ@<fn>{faq}を参考にしてください。

===[/column]

//footnote[ogp][OGPはOpen Graph Protcolの略です。HTMLにメタデータとして「og:image」のようなOGPタグを書いておくことで、TwitterやLINEなどでそのURLを共有したときに、URLそのままではなく対象ページのタイトルや概要、画像などがカードのように表示されます。]
//footnote[card-validator][TwitterのCard Validator（@<href>{https://cards-dev.twitter.com/validator}）とか、Facebookのシェアデバッガー（@<href>{https://developers.facebook.com/tools/debug/}）みたいなものですね。TwitterのCard Validatorは気づいたらプレビュー確認機能がなくなっていましたが……。]
//footnote[faq][トークとLINE VOOM内のURLプレビューはどのようにして生成されますか？ | LINE Developers @<href>{https://developers.line.biz/ja/faq/#how-are-the-url-previews-generated}]

=== Flex Messageで見た目にこだわったメッセージを送る

もっと格好良い、見た目にこだわったメッセージを送りたい！と思ったら、Flex Message Simulatorを使ってみましょう。

 * Flex Message Simulator@<fn>{login}
 ** @<href>{https://developers.line.biz/flex-simulator/}

//footnote[login][Flex Message Simulatorを使うときは、LINE Developersコンソールと同じようにLINEアカウントでログインする必要があります。]

GUIでレイアウトをカスタマイズするだけで、メッセージのJSON@<fn>{notice}が生成される素晴らしいツールです。（@<img>{flex-message-1}）

//image[flex-message-1][Flex Message Simulatorで見た目にこだわったメッセージをつくってみよう][scale=0.8]{
//}

//footnote[notice][ただしFlex Message Simulatorで出力されるJSONは、messages直下のFlex Message全体ではなく、コンテナ（contents以下）なので注意が必要です。Flex Messageの仕様については、APIリファレンスを参照してください。 @<href>{https://developers.line.biz/ja/reference/messaging-api/#flex-message}]

しかも「このFlex Messageを送ったら実際はどんな見た目になるんだろう？画像は見切れないかな？」と思ったら、右上の［Send...］からメッセージをテスト送信できるのです。便利！（@<img>{flex-message-2}、@<img>{flex-message-3}）

//image[flex-message-2][Flex Message Simulatorからテスト送信する][scale=0.8]{
//}

//image[flex-message-3][Flex Message SimulatorのLINE公式アカウントからメッセージが届く][scale=0.6]{
//}

=== ボットサーバーがWebhookを受け取れなかったときの再送機能

たとえばLINE公式アカウントが急に有名になり、一気に友だちが増えて、メッセージが大量に送られてきたとします。急なアクセス集中でサイトが落ちるように、LINEプラットフォームから飛んでくるWebhookのリクエストによって、ボットサーバーが過負荷になって応答できなくなってしまったらどうなるのでしょうか。

そんなときのために「Webhookの再送@<fn>{retry-webhook}」という機能があります。Webhookの再送はデフォルトではオフになっていますが、LINE Developersコンソールでオンにすることで、ボットサーバーがWebhookを受け取れなかったときに再送してくれるようになります。

//footnote[retry-webhook][受け取りに失敗したWebhookを再送する | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/receiving-messages/#webhook-redelivery}]

どこで「Webhookを受け取れなかった」と判断されるのかというと、LINEプラットフォームから見て、「Webhookを受け取ってー！」というリクエストに対してきちんとステータスコード200が返ってこなければ「ボットサーバーはWebhookを受け取れなかった」と判断されます。

とても便利に見えるWebhookの再送機能ですが、ボットサーバーから見て「Webhookを受け取ってー！」というリクエストに対して、きちんとステータスコード200を返したつもりでも、ボットサーバーからLINEプラットフォームまでのネットワーク経路上で何か問題があって、きちんとレスポンスがLINEプラットフォームまで到達しないケースは考えられます。その場合、Webhookの再送をオンにしたことで次のようなトラブルが考えられます。

 1. ユーザーが『購入する』というメッセージを送信する
 1. LINEプラットフォームからボットサーバーに『購入する』というメッセージのWebhookが飛ぶ
 1. ボットサーバーでWebhookを受け取ってステータスコード200を返し、商品購入処理を行った上でユーザーに「購入完了しました！」という応答メッセージを送る
 1. しかし何らかの理由でステータスコード200のレスポンスがLINEプラットフォームに到達しなかった
 1. LINEプラットフォームは「ボットサーバーがWebhookを受け取れなかった」と判断して、『購入する』というメッセージのWebhookを再送する
 1. ボットサーバーでWebhookを受け取ってステータスコード200を返し、商品購入処理を行った上でユーザーに「購入完了しました！」という応答メッセージを送る
 1. ユーザーは一度『購入する』と送っただけなのに、商品が2つ購入されてしまい、購入完了メッセージも2度届いて驚く

これを防ぐためには、ボットサーバー側で商品購入処理を行う際に、Webhookのイベントごとに一意な値である@<ttb>{webhookEventId}を確認して、「既に購入処理を行ったWebhookイベントと同一のイベントではないか？」を確認する必要があります。

Webhookの再送は便利な機能ですが、このように意図しない再送が行われたときのことを考えた重複チェックの処理がなければ、迂闊にオンにするべきではありません。

=={richmenus} リッチメニュー

LINE公式アカウントと友だちになると、トーク画面の下部にこんなメニューが表示されることがありますよね。これは簡素なテキストではなく、画像でできた贅沢で多彩なメニュー…つまりリッチなメニュー…リッチなメニューなので…リッチメニュー！そう、これがリッチメニュー@<fn>{richmenu-link}です。（@<img>{richmenu}）

//footnote[richmenu-link][リッチメニューを使う | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/using-rich-menus/}]

//image[richmenu][リッチメニュー][scale=0.4]{
//}

このリッチメニューは、一番下の「新刊を読む！▼」と書いてあるバーをタップすることで開いたり閉じたりできます。このバーのテキストも、デフォルトの「メニュー」から「メニューはこちら」「お問い合わせの入力はこちら」「ほっとするブレイクタイムを」「会員証」「お役立ち情報はこちら」「人気ランキングをチェック！」「こちらもチェック」「荷物の追跡・再配達・集荷受付」といった様々なテキストに変更できます。

リッチメニューの実態は次のような1枚の画像であり、画像内の各領域にそれぞれリンクを設定することで、公式サイトや予約ページ、特定の機能などにユーザーを誘導できます。（@<img>{richmenu-example}）

//image[richmenu-example][リッチメニューの画像][scale=0.6]{
//}

=== リッチメニュープレイグラウンドでリッチメニューを体験してみよう

リッチメニューの様々な機能は、文字で説明するより体験してみるのが一番分かりやすいです。公式で提供されているリッチメニュープレイグラウンドという、「リッチメニューを体験するためのLINE公式アカウント」と友だちになってみましょう。（@<img>{richmenu-playground-qrcode}）

//image[richmenu-playground-qrcode][リッチメニュープレイグラウンドと友だちになる][scale=0.3]{
//}

［リッチメニューを開く▼］をタップすると、［メッセージアクションを試す］と表示されました。これは「ユーザーがリッチメニューをタップすることで、特定のメッセージをユーザーから自動送信させる」という機能です。早速［メッセージ送信］を試してみましょう。（@<img>{add-richmenu-playground}）

//image[add-richmenu-playground][［メッセージ送信］をタップするとメッセージが送信されて返信が届いた][scale=0.8]{
//}

あなたが文字を入力した訳ではないのに、［message sent successfully!］というメッセージがあなたから送信されました。これがメッセージアクションです。メッセージアクションによって、ユーザーからLINE公式アカウントに対して自動でメッセージが送られ、それによってWebhookがボットサーバーに届きました、という一連の流れを解説してくれています。

たとえば「再配達の申し込みをしたかったら、LINEで『再配達』というメッセージを送ってね」のように、ユーザーに手入力を促さなくても、リッチメニューに「再配達の申し込み」というボタンを用意して、そのボタンの領域をタップしたら「再配達」というメッセージが自動送信されるよう、対象の領域にメッセージアクションを設定しておけばいいのです。このように「この機能はこんな風に使えばいいのか」を体験できるのがリッチメニュープレイグラウンドのいいところです。

=== リッチメニューの画像を作る

リッチメニューの画像を作ろうと思うと意外と大変です。LINE Official Account Managerでリッチメニューの作成画面を開くと、「デザインガイド」というボタンがあり、そこからリッチメニューのテンプレート画像がダウンロードできます。Messaging APIを使ったリッチメニューの設定を試したい場合は、このテンプレートをそのまま使ってみるのがお勧めです。（@<img>{richmenu-template}）

//image[richmenu-template][リッチメニューのテンプレート画像がダウンロードできる][scale=1]{
//}

=== LINE Official Account ManagerとMessaging APIでのリッチメニューの制約の違い

リッチメニューはMessaging APIで頑張ってJSONを組み立てて作らなくても、実はLINE Official Account Managerで画像やテキストを組み合わせて作ることも可能です。

ただしLINE Official Account Managerでリッチメニューを作る場合、大が7種類、小が5種類という特定のサイズや形からしか選べません。また全員に同じリッチメニューを出す機能しかないため、会員証を持っている人にだけ会員向けのリッチメニューを出す、といった出し分けもできません。Messaging APIであれば、縦横のサイズや、それぞれの領域も自由に設定でき、ユーザーごとに別々のリッチメニューを表示させることも可能ですし、タブ切り替えのようなリッチメニューを作ることもできます。

限定された機能で構わないのでラクにリッチメニューが設定したいならLINE Official Account Managerを使って、こだわったリッチメニューが設定したいならMessaging APIを使うのが良いでしょう。

== Messaging APIをもっと楽しむために

ここまでMessaging APIを使ってLINE Botを作ってきましたがいかがでしたか？楽しんでもらえましたか？

最後に、一歩踏み出したあなたがこれからMessaging APIをもっと楽しむために、「この先にはこんな道やあんな道がありますよ」という、さまざまな道のご紹介をしたいと思います。

=== Messaging API以外のプロダクトとの組み合わせ

LINE APIには、Messaging APIの他に、LINEログインやLIFF (LINE Front-end Framework) やLINEミニアプリ、LINE Social Pluginsなどさまざまなプロダクトがあります。Messaging API単体でできることが把握できたら、他のプロダクトと組み合わせるとさらにどんなことができるのか、LINE Developersサイトで見てみましょう。

 * LINE Developersサイト
 ** @<href>{https://developers.line.biz/}

=== LINEキャンパスで資格を取ってみよう

「Messaging APIの前提知識として、もう少しLINE公式アカウントについて学びたい」という場合は総合学習プラットフォーム「LINEキャンパス」がお勧めです。「LINE公式アカウント Basic」と「LINE公式アカウント Advanced」という認定資格の取得を目指して、学習コースや資格認定コースを無料で受講してみましょう。

 * LINEキャンパス
 ** @<href>{https://campus.line.biz/}

=== LINE Creative Labを使おう

LINE Creative Labを使うと、画像メッセージとして送れる素材が簡単に作れます。クリエイティビティにあふれた画像や動画を作って、Messaging APIで送ってみましょう。

 * LINE Creative Lab
 ** @<href>{https://creativelab.line.biz/}

=== パソコン版のLINEを使おう

意外と知らない人が多いのですが、実はスマートフォンで使っているLINEと同じアカウントで、パソコン版のLINEも使うことができます。Messaging APIの動作検証をするため、LINE公式アカウントにメッセージを送る場合は、PC版のLINEで作業した方がやりやすいです。ただしリッチメニューなど、パソコン版のLINEではサポートされていない機能も一部ありますので注意してください。

 * パソコンでLINEを利用する｜LINEみんなの使い方ガイド
 ** @<href>{https://guide.line.me/ja/services/pc-line.html}

=== LINE Developers Communityに参加しよう

LINE APIを活用している有志によって、LINE Developers Communityのイベントが定期的に開催されています。LINE API Expertとして認定されたみなさんが、最新機能や開発手法をオンラインで教えてくれるので、開発で行き詰まったらひとりで悩まずにコミュニティに参加してみるのがお勧めです。LINE Developers communityのサイトにはユーザー同士のQ&Aもあり、開発でつまづいたときは質問を投稿したり、過去の質問からヒントを探したりできます。

 * LINE Developers Community
 ** @<href>{https://www.line-community.me/}
