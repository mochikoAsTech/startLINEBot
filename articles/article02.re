= Messaging APIでLINE Botをつくってみよう

LINE公式アカウントの「中の人」を、人間の代わりにボットにしてみましょう。

//pagebreak

== LINE公式アカウントをチャットボットにしたい

@<chapref>{article01}ではLINE公式アカウントを作り、管理アプリを使って友だちにメッセージを送信しました。LINE公式アカウント管理アプリやLINE Official Account Managerには色んな機能があるので、それらを使ってお店やサービスのLINE公式アカウントを運用していくことも可能です。

ですが、本書ではLINE公式アカウントを手作業で運用していきたい訳ではなく、「中の人」を人間からボットに変えて、LINE公式アカウントを自動で応答するチャットボットにしたいのです。

=== チャットボットとは

急にチャットボットという言葉が出てきましたが、チャットボットとはいったいなんでしょう？

チャットボットとは、リアルタイムにメッセージをやりとりする「チャット」と、人間のように動いたり働いたりする機械の「ロボット」を組み合わせた言葉です。チャットボットの裏側には人間がいるわけではなく、プログラムがメッセージの内容に応じた返信をしてくれたり、自動でメッセージを送ってきたりしています。

このチャットボットは、近年では身近な存在になったことで、単に「ボット」と呼ばれることの方が多いかもしれません。Twitterで地震が起きるとすぐに震度を知らせてくれる地震速報ボットや、著名人の名言を定期的につぶやくボット、特定の用語に反応してリプライしてくるボットなどを、あなたも一度は見たことがあるのではないでしょうか。会社のSlackに、GitHubの通知をしてくれるボットや、メッセージを自動翻訳してくれるボットがいる、というケースもあるかも知れません。

本書では、この自動応答するチャットボットのプログラムのことを「ボット」と呼びます。

== Messaging APIでチャットボットを作るには

ボットを作って、LINE公式アカウントをチャットボットにするには、LINEのMessaging APIというものを使います。

=== APIとは

さて、Messaging APIとは何か、という話をする前に、そもそも「API」とは何か、という説明をさせてください。

Messaging APIの「API」は、Application Programming Interfaceの略です。名前のとおり、別々のアプリケーションがお互いに情報をやりとりするときの接点となる、窓口のようなものだと思ってください。そして本来、APIはとても広い意味をもつ言葉ですが、このMessaging APIにおけるAPIとは「REST API」@<fn>{restful}のことだと思われます。

//footnote[restful][RESTはREpresentational State Transferの略。RESTアーキテクチャスタイルという、ルールのようなものに従って作られたAPIがREST APIやRESTful APIと呼ばれます。]

通常、私たちはブラウザでURLを入力したり、リンクをクリックしたりすることで「このウェブページを見せてくれ！」とウェブサーバーにリクエストを投げ、リクエストを受けたウェブサーバーが「はい、どうぞ」とウェブページをレスポンスで返してくれます。（@<img>{request-and-response}）

//image[request-and-response][ブラウザでウェブページを見るときのリクエストとレスポンス][scale=1]{
//}

REST APIは、このウェブページと同じように、ウェブサーバー上で提供されます。私たちがcurlコマンド@<fn>{curl}や、Postman@<fn>{postman}や、プログラムを通じてREST APIに対して「天気情報をくれ！」とか「メッセージを送信してくれ！」というリクエストを投げると、ウェブサーバー上でうごくREST APIが「はい、どうぞ！君が求めていた天気情報はこれだよ！」とか「メッセージの送信に成功したよ！」というようにレスポンスを返してくれるのです。（@<img>{api-request-and-response}）

//footnote[curl][curk（カール）はHTTPやHTTPS、SCP、LDAPなど、さまざまなプロトコルでデータ転送ができるコマンドです。今までにcurlを使ったことのない人とっては、この説明を読んでもいまいちピンとこないと思うので、「ターミナル」という種類のソフトで、ブラウザのようなことができるコマンドだと思っておいてください。ちなみにターミナルは、エンジニア以外の方には、いわゆる「黒い画面」と言った方がお馴染みかもしれません。]
//footnote[postman][Postmanは、GUIの画面でREST APIをたたける便利なツールです。 @<href>{https://www.postman.com/}]

//image[api-request-and-response][REST APIをたたくときのリクエストとレスポンス][scale=1]{
//}

前述のとおり、APIは広義には「情報をやりとりする窓口」であり、様々な意味を内包していますが、本書においてはただ「API」と呼んだら、それはREST APIのことを指していると思ってください。

=== Messaging APIとは

ではあらためて、Messaging APIについて説明していきましょう。Messaging APIは、LINE公式アカウントからのメッセージ送信や、返信などの操作ができるAPI@<fn>{use-messaging-api}です。LINE株式会社が無料で提供しており、LINE Developersコンソールと呼ばれる開発者向けの管理画面でアカウント登録をすれば誰でも利用できます。@<fn>{price}

//footnote[use-messaging-api][Messaging APIは、あくまでLINE公式アカウントの操作をするためのAPIなので、個人のLINEアカウントで受信したメッセージをSlackに転送する、というようなことはできません。]
//footnote[price][Messaging APIの各APIをたたくこと自体に費用はかかりません。@<chapref>{article01}の@<hd>{article01|oaprice}で紹介したとおり、送れるメッセージの通数を増やすために有料のプランを契約したときに初めてお金がかかります。]

Messaging APIを使用することで、開発者はユーザーがLINE公式アカウントに送ったメッセージを受信したり、LINE公式アカウントから友だちに対して返信を送ったり、友だちとなったユーザーのプロフィール情報を取得したりすることができます。

実際にMessaging APIを使用するためには、LINE公式アカウントと紐づく形でMessaging APIチャネルというものを作って、APIの利用に必要な「チャネルアクセストークン」を取得する必要があります。

LINE公式アカウントとMessaging APIチャネルの関係は、初見だとちょっと分かりにくいので、実際にMessaging APIチャネルを作る前にそこを少し説明していきます。

== Messaging APIチャネルを作ろう

LINE公式アカウントとMessaging APIチャネルは、表と裏のような存在です。LINE公式アカウントを単体で作って、LINE Official Account Managerや管理アプリを使って中の人が頑張ることもできますが、裏側にMessaging APIチャネルを紐づけて、ボットが自動で応答するように設定することも可能です。（@<img>{messaging-api-channel}）

//image[messaging-api-channel][LINE公式アカウントとMessaging APIチャネルは表と裏][scale=1]{
//}

あなたはさっき、LINEでLINE公式アカウントを作ったので、いまは表のLINE公式アカウントだけがあって、裏に控えるMessaging APIチャネルはまだ存在していない状態です。

前述のLINE DevelopersコンソールでMessaging APIチャネルを作ると、最初から表（LINE公式アカウント）と裏（Messaging APIチャネル）が揃った状態で作成されるのですが、先に表だけを作った場合は、LINE Official Account Managerで裏を作って紐づけてやる必要があります。

それではLINE Official Account Managerで、あなたのLINE公式アカウントに紐づくMessaging APIチャネルを作りましょう。

==={login-oamanager} LINE Official Account Managerにログインする

@<chapref>{article01}では、スマートフォンで色々な操作をしていましたが、ここからはパソコンで作業します。

Messaging APIチャネルを作成するため、LINE Official Account Managerを開いてください。

 * LINE Official Account Manager
 ** @<href>{https://www.linebiz.com/jp/login/}

左側の［管理画面にログイン］から、LINE公式アカウントの管理画面こと、LINE Official Account Managerにログインします。（@<img>{line-for-business-login}）

//image[line-for-business-login][［管理画面にログイン］からログインする][scale=0.8]{
//}

LINEビジネスID@<fn>{business-id}のログイン画面が表示されるので、［LINEアカウントでログイン］を選択します。（@<img>{line-for-business-login-2}）

//footnote[business-id][LINEビジネスIDはLINE Official Account Manager、LINE公式アカウントの管理アプリ、LINE Developersコンソールなどで採用されている共通認証システムで、1つのアカウントですべてに共通してログインできます。実はさっき管理アプリにログインしたときも、この共通認証システムを使っていたのです。]

//image[line-for-business-login-2][［LINEアカウントでログイン］を選ぶ][scale=0.8]{
//}

@<hd>{article01|create-account}で登録したメールアドレスと、LINEのパスワード@<fn>{password}を入力して、［ログイン］しましょう。入力が面倒な場合は、［QRコードログイン］からQRコードを表示して、それをスマートフォンのLINEのQRコードスキャンで読み込む形でもログイン可能です。（@<img>{line-for-business-login-3}）

//footnote[password][「LINEのパスワードなんて設定したっけ？何も覚えていません」という人はLINEを開いて、下に並んでいる［ホーム］から右上の歯車アイコンをタップして［設定］を開き、［アカウント］の［パスワード］からすぐに新しいパスワードを設定できます。 @<href>{https://guide.line.me/ja/account-and-settings/account-and-profile/set-password.html}]

//image[line-for-business-login-3][メールアドレスとパスワードを入力して［ログイン］する][scale=0.8]{
//}

二要素認証のため、4桁の認証番号が表示されます。（@<img>{line-for-business-login-4}）

//image[line-for-business-login-4][4桁の認証番号が表示される][scale=0.8]{
//}

スマートフォンのLINEを開くと、認証番号入力の画面が表示されますので、4桁の認証番号を入力して［本人確認］をタップします。［ログインしました］と表示されたら、［確認］をタップします。（@<img>{line-for-business-login-5}）

//image[line-for-business-login-5][認証番号を入力して［本人確認］をタップする][scale=0.8]{
//}

これでLINE Official Account Managerにログインできました！（@<img>{line-for-business-login-6}）

//image[line-for-business-login-6][LINE Official Account Managerにログインできた][scale=0.8]{
//}

=== Messaging APIチャネルを作って紐づける

ではアカウントリストから、先ほど作ったLINE公式アカウントを選択します。（@<img>{line-for-business-login-7}）

//image[line-for-business-login-7][先ほど作ったLINE公式アカウントを選択する][scale=0.8]{
//}

右上にある［設定］を開きます。（@<img>{create-messaging-api-channel}）

//image[create-messaging-api-channel][右上にある［設定］を開く][scale=0.8]{
//}
     
左メニューの［設定］の配下にある［Messaging API］を開きます。（@<img>{create-messaging-api-channel-2}）

//image[create-messaging-api-channel-2][左メニューの［Messaging API］を開く][scale=0.8]{
//}
     
［Messaging APIを利用する］を開きます。（@<img>{create-messaging-api-channel-3}）

//image[create-messaging-api-channel-3][［Messaging APIを利用する］を開く][scale=0.8]{
//}

まだLINE Developersコンソールにログインしたことがなかったため、開発者情報の入力を求められます。ここでいう「開発者」とは、イコール「LINE Developersコンソールにアクセスする人のこと」です。あなたの［名前］@<fn>{mochiko}と［メールアドレス］@<fn>{mail-address}を入力して、リンク先の「LINE開発者契約」を確認した上で、同意できる内容であれば［同意する］を押します。（@<img>{create-messaging-api-channel-5}）

//footnote[mochiko][筆者は［名前］の欄に個人事業主としての屋号（mochikoAsTech）を記入していますが、個人開発者として登録するのであれば普通に氏名の入力で構わないと思います。]
//footnote[mail-address][ここで登録するメールアドレスは、LINEに登録してあるメールアドレスとは別のアドレスでも構いません。開発者に対するお知らせを送ってほしいメールアドレスを記入しましょう。ただしLINE Developersコンソールへのログインに使用するメールアドレスは、LINEに登録してあるメールアドレスであって、ここで記入したメールアドレスではないので、その点は注意してください。]

//image[create-messaging-api-channel-5][［名前］と［メールアドレス］を入力して［同意する］を押す][scale=0.8]{
//}
     
入力した開発者情報の確認画面が表示されます。表示されている内容で問題なければ、［OK］を押します。（@<img>{create-messaging-api-channel-6}）

//image[create-messaging-api-channel-6][表示されている内容で問題なければ［OK］を押す][scale=0.8]{
//}

開発者情報を登録すると、今度はプロバイダーの選択画面が表示されます。プロバイダーとは、サービスを提供し、ユーザーの情報を取得する企業や開発者個人のことを指し、これから作成するMessaging APIチャネルは、このプロバイダーというものの下に属します。プロバイダーの下には、複数のチャネルが所属できます。

運営元が個人だと「チャネルも俺！プロバイダーも俺！全部俺だ！」みたいな気持ちになって違いが分かりにくいですが、たとえば飲料メーカーのA社が「炭酸飲料B」と「コーヒー飲料C」という2つのブランドを展開していた場合、プロバイダー名は「A社」になり、その配下にあるMessaging APIチャネル名は「炭酸飲料B」や「コーヒー飲料C」になります。@<fn>{provider}（@<img>{providers-and-channels}）

//image[providers-and-channels][チャネルはプロバイダーの配下に属する][scale=0.6]{
//}

//footnote[provider][複数のチャネルがあって、それらを1つのプロバイダー配下に収めたときと、それぞれプロバイダーを別にしたときで何が変わるかというと、ユーザーIDの扱いが変わります。ユーザーを一意に識別するためのユーザーIDは、同じユーザーであってもプロバイダーごとに異なる値が発行されます。つまりmochikoさんというひとりのユーザーがいたとき、「A社」というプロバイダーの配下にあるチャネルから見たmochikoさんのユーザーIDと、また別の「B社」というプロバイダーの配下にあるチャネルからみたmochikoさんのユーザーIDは別々の値になるのです。そのため、本書では詳しく触れませんがLINEログインチャネルとMessaging APIチャネルでユーザー情報を連携したい場合は、その2つのチャネルが同一のプロバイダー配下にいなければならない、などの制約があります。一度チャネルをプロバイダーと紐づけてしまうと、後から「あっちのプロバイダー配下に移動させたい！」と思っても、絶対に移動できないので注意してください。]

あなたが個人の開発者なのであれば、プロバイダー名は個人名でも構いません。誰かに「このLINE公式アカウントの運営元はどこなんですか？」と聞かれたときに、あなたが答えるであろう名称をプロバイダー名にしましょう。

まだプロバイダーというものを1つも持っていないので、今回は［プロバイダーを作成］します。プロバイダー名を入力して、「LINE公式アカウントAPI利用規約」を確認し、［同意する］を押します。（@<img>{create-messaging-api-channel-7}）

//image[create-messaging-api-channel-7][プロバイダー名を入力して［同意する］を押す][scale=0.8]{
//}
     
もしあなたがサービス提供者として、プライバシーポリシーや利用規約を既に持っていたら、プロバイダーのプライバシーポリシーと利用規約としてここでURLを登録できます。個人開発者であればおそらくどちらも持っていないと思いますので、その場合は何も入力せずに［OK］を押して進んで構いません。（@<img>{create-messaging-api-channel-8}）

//image[create-messaging-api-channel-8][入力せずに［OK］を押す][scale=0.8]{
//}

このLINE公式アカウントを、このプロバイダー配下のMessaging APIチャネルと紐づけますがいいですか、という最終確認の画面が表示されます。記載のとおり、一度チャネルをプロバイダーと紐づけてしまうと、後から「あっちのプロバイダー配下に移動させたい！」と思っても、絶対に移動できないので、プロバイダー名はよく確認してください。問題なければ［OK］を押します。（@<img>{create-messaging-api-channel-9}）

//image[create-messaging-api-channel-9][確認して［OK］を押す][scale=0.8]{
//}
     
これでLINE公式アカウントと紐づくMessaging APIチャネルができました！（@<img>{create-messaging-api-channel-10}）

//image[create-messaging-api-channel-10][確認して［OK］を押す][scale=0.8]{
//}

== Messaging APIを使ったメッセージ送信を試してみよう

それではMessaging APIチャネルができたので、早速Messaging APIを使ってメッセージを送信してみましょう。

==={issue-token} LINE Developersコンソールでチャネルアクセストークンを発行する

Messaging APIを使ってメッセージを送信するにあたって、前述したチャネルアクセストークンというものが必要なので、LINE Developersコンソールを開きます。

 * LINE Developersコンソール
 ** @<href>{https://developers.line.biz/console/}

既にLINE Official Account Managerにログインしていれば、上記のURLを開くと、そのままLINE Developersコンソールのプロバイダー一覧が表示されるはずです。もしログインを求められたら、@<hd>{article02|login-oamanager}と同じようにLINEのアカウントでログインしてください。プロバイダー一覧が表示されたら、左メニューで、先ほど作ったプロバイダーを選びます。（@<img>{console}）

//image[console][LINE Developersコンソールのプロバイダー一覧が表示された][scale=0.8]{
//}

プロバイダーを選ぶと、そのプロバイダーの配下にあるチャネルの一覧が表示されます。続いて、同じく先ほど作ったMessaging APIチャネルを選びます。（@<img>{console-2}）

//image[console-2][プロバイダー配下のチャネル一覧が表示された][scale=0.8]{
//}

Messaging APIチャネルが表示されたら、［チャネル基本設定］タブの右隣にある［Messaging API設定］タブを開いてください。（@<img>{console-3}）

//image[console-3][先ほど作ったMessaging APIチャネルが表示された][scale=0.8]{
//}

［Messaging API設定］タブをいちばん下までスクロールすると、［チャネルアクセストークン（長期）］があります。［発行］を押して、長期のチャネルアクセストークンを発行してください。（@<img>{console-4}）

//image[console-4][［発行］を押して長期のチャネルアクセストークンを発行する][scale=0.8]{
//}

このチャネルアクセストークン@<fn>{access-token}は、Messaging APIを使うときに、自分がそのMessaging APIチャネルの持ち主であることを証明する身分証のような役割を果たします。うっかりチャネルアクセストークンが載った画面をブログで公開したり、ソースコードに直接書いてGitHubにPushしたりしないように注意してください。

//footnote[access-token][チャネルアクセストークンにはいくつか種類がありますが、本書では説明を割愛し、この長期のチャネルアクセストークンを使用します。 @<href>{https://developers.line.biz/ja/docs/messaging-api/channel-access-tokens/}]

長期のチャネルアクセストークンを発行したら、右側のコピーボタンを押してコピーします。［コピーしました］と表示されます。（@<img>{console-5}）

//image[console-5][発行したチャネルアクセストークンをコピーする][scale=0.8]{
//}

いまコピーしたチャネルアクセストークンはこの後で何度も必要となります。忘れないように、パソコンのメモ帳にしっかりメモしておいてください。

チャネルアクセストークンと同じように後で必要となるため、続いて［チャネル基本設定］タブのチャネルシークレットもコピーして、一緒にメモしておきましょう。（@<img>{console-6}）

//image[console-6][チャネルアクセストークンもコピーする][scale=0.8]{
//}

チャネルアクセストークンとチャネルシークレットが手に入ったので、早速Messaging APIでメッセージを送ってみましょう。

==={curl} Messaging APIでブロードキャストメッセージを送信する

実は、ただメッセージを送るだけならウェブサーバーは必要ありません。あなたのパソコンでcurlコマンドをたたくことで、Messaging APIを使ってメッセージを送信できます。あなたが使っているパソコンがWindowsならWSL（@<img>{wsl}）@<fn>{wsl}を起動してください。

//image[wsl][WindowsならWSLを起動する][scale=0.8]{
//}

//footnote[wsl][WSLとはWindows Subsystem for Linuxの略で、Windows上で動くLinux環境のことです。]

Macを使っている方は、ターミナル（@<img>{mac}）を起動してください。

//image[mac][Macならターミナルを起動する][scale=0.8]{
//}

WSLやターミナルがどこにあるのか分からないときは、Windowsなら画面下部の検索ボックスで「WSL」と検索（@<img>{search-wsl}）、Macなら画面右上にある虫眼鏡のマークからSpotlightで「ターミナル」と検索（@<img>{search-mac}）すれば起動できます。

//image[search-wsl][Windowsなら検索ボックスで「WSL」と検索][scale=0.8]{
//}

//image[search-mac][MacならSpotlightで「ターミナル」と検索][scale=0.8]{
//}

WSLまたはターミナルが起動できたら、次のcurlコマンド（@<list>{curl-send-message}）の3行目にある「チャネルアクセストークン」の部分を、Messaging APIチャネルのチャネルアクセストークンに置き換えてください。チャネルアクセストークンは、先ほど@<hd>{article02|issue-token}でコピーしましたね。

//listnum[curl-send-message][curlコマンドで友だちにメッセージを送る][sh]{
curl -v -X POST https://api.line.me/v2/bot/message/broadcast \
-H 'Content-Type: application/json' \
-H 'Authorization: Bearer チャネルアクセストークン' \
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
//}

チャネルアクセストークンを置き換えたら、curlコマンドをまるごとコピーしてWSLもしくはターミナルに貼り付けます。WSLの場合は、複数行をまとめて貼り付けると警告が出ますが、［強制的に貼り付け］を押します。（@<img>{curl-1}）

//image[curl-1][複数行の貼り付けに対する警告が出たら［強制的に貼り付け］を押す][scale=0.8]{
//}

貼り付けたらEnterを押して実行します。（@<img>{curl-2}）

//image[curl-2][貼り付けたらEnterを押して実行する][scale=0.8]{
//}

レスポンスが画面に出力されます。curlコマンドを使ってAPIをたたいた結果、レスポンスとしてステータスコード200と空のJSONオブジェクトが返ってきたことが分かります。（@<img>{curl-3}）

//image[curl-3][ステータスコード200が返ってきた][scale=0.8]{
//}

すると、Messaging APIで送ったメッセージがLINEに届きました！（@<img>{broadcast-message}）

//image[broadcast-message][Messaging APIで送ったメッセージが届いた][scale=0.4]{
//}

やったぁ！Messaging APIがたたけましたね！おめでとうございます。

いまあなたがたたいたのは、LINE公式アカウントと友だちになっている人全員にメッセージを送るための「ブロードキャストメッセージを送る」いうAPIです。もしcurlコマンドを実行した後にステータスコード200以外が返ってきて、LINEにメッセージが届かなかった場合は、公式ドキュメントのAPIリファレンス@<fn>{broadcast-message}でこの「ブロードキャストメッセージを送る」いうAPIのエラーレスポンス例を確認してみてください。

//footnote[broadcast-message][ブロードキャストメッセージを送る | Messaging APIリファレンス | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#send-broadcast-message}]

メッセージが届いたら、curlコマンドのtextの部分を好きなテキストにしたり、公開されている「送信可能なスタンプリスト@<fn>{stamp}」を見ながらcurlコマンドのpackageIdやstickerIdを好きなものに変えてみたりして、メッセージを何度か送り直してみましょう。（@<img>{broadcast-message-2}）

//image[broadcast-message-2][テキストやスタンプを変えてメッセージを何度か送ってみよう][scale=0.4]{
//}

//footnote[stamp][送信可能なスタンプリスト | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/sticker-list/}]

curlコマンドでAPIをたたくと、手元のスマートフォンでLINEにメッセージが届く。こうして自分がやったことが、ちゃんと動いて、結果が目に見えるのはとってもうれしいですよね。

===[column] 【コラム】仕事でLINE Botを開発するときにも「個人のLINEアカウント」が必要か？

Messaging APIを使って開発をするとき、様々な設定をするための管理画面が「LINE Developersコンソール」です。このLINE Developersコンソールにログインするには、LINEアカウントまたはビジネスアカウントのどちらかが必要です。

すでにスマートフォンでLINEを使っていれば、そのLINEアカウントでそのままログインできます。本書では、@<chapref>{article01}でLINE公式アカウントを作ったときのLINEアカウントで、LINE Developersコンソールにログインしています。

個人開発であればこれで問題ありませんが、仕事の場合は「私物のスマホに入れている個人のLINEアカウントを業務で使うのはちょっと…」というケースももちろんあると思います。その場合は業務用のメールアドレスでビジネスアカウントを作りましょう。ただしビジネスアカウントでLINE Developersコンソールにログインした場合は、Messaging APIチャネルが作れないなど、できることに一部制限@<fn>{limited}があります。

その場合は、プロジェクトの中で誰かひとりが会社の検証端末にLINEを入れ、そのLINEアカウントでLINE Developersコンソールにログインして、Messaging APIチャネルを作ればいいのです。後はそのプロバイダーやチャネルに、他のメンバーのビジネスアカウントをAdmin権限で追加してやれば、開発を進める上で問題はないでしょう。

===[/column]

//footnote[limited][LINE Developersコンソールへのログイン | LINE Developers @<href>{https://developers.line.biz/ja/docs/line-developers-console/login-account/}]

== LINE公式アカウントから友だちに返信するには

さて、ここまでは「LINE公式アカウントからメッセージを送る」という、LINE公式アカウント起点の話をしてきました。LINE公式アカウント起点というのは、たとえば月初に今月の定休日を知らせるメッセージを送るとか、新商品が出たときにメッセージを送るとかいうように、LINE公式アカウント側が「送りたい！」と思った任意のタイミングでメッセージを送る、ということです。

でも片方が話したいときだけ一方的に話すのでは、それは対話とは言えません。ユーザーが友だち追加してくれたときや、ユーザーが何か質問してきたとき、ユーザーがリッチメニュー@<fn>{rich}をタップしたときなど、ユーザー起点のコミュニケーションにきちんと反応できるようになってこそのチャットボットです。

//footnote[rich][リッチメニューについては、@<hd>{article03|richmenus}で後述します。]

ではユーザー起点のメッセージにLINE公式アカウントが反応するには、どうしたらいいのでしょう？ユーザーからのメッセージに応対する方法は、大きく分けて4つあります。

==={reply} 方法1. 固定の自動応答を設定しておいて個別応対は一切しない

1つめは、LINE Official Account Managerで次のような固定の「応答メッセージ」を設定しておいて、個別の応対は一切しないという方法です。@<hd>{article01|try-message}で「新刊買います！」というメッセージを送ったときに受け取った返信なので見覚えがありますね。（@<img>{auto-res}）

//image[auto-res][自動の応答メッセージ][scale=0.6]{
//}

この自動の応答メッセージは、LINE公式アカウントを作ったときにデフォルトで設定されているので、あなたも友だち追加したLINE公式アカウントでよく似たメッセージを見たことがあるかもしれません。

これだと個別対応のコストが一切要らなくなるものの、ユーザー起点のコミュニケーションはできなくなるので、LINE公式アカウントとのトークは一方的な宣伝をするだけの場所になります。ただ、少なくとも話しかけたのに何も応答せず無言でいられるよりは、まだ気分がいいかもしれません。

=== 方法2. 人間が手打ちのチャットで返信する

2つめは、「中の人」が頑張って手打ちのチャットで返信する、という方法です。LINE Official Account Managerや管理アプリにはチャットの機能があるので、「中の人」がその機能でユーザーからのメッセージを確認して、手打ちのチャットで頑張って応対します。

たとえば個人で経営する小さなヘアサロンで、予約を電話ではなくLINEのトークで受け付けたい、というような場合は、このチャットで必要十分なケースもあるでしょう。

=== 方法3. 内容に応じた自動応答メッセージで応対する
     
3つめは、内容に応じた自動応答メッセージを用意しておいて自動で返信する、という方法です。

LINE Official Account Managerや管理アプリには、応答メッセージとAI応答メッセージ@<fn>{reply_and_ai}というものがあります。応答メッセージはキーワードとメッセージを事前に設定しておくことで、ユーザーがそのキーワードと完全一致するメッセージを送ってきたら、自動でメッセージを返信する機能です。完全に一致する必要があるので、たとえば「メニュー」というキーワードの場合、ユーザーが「メニュー」とだけ送ってくれば応答できますが、「メニューは？」と送ってきた場合は応答できません。

//footnote[reply_and_ai][自動応答が可能に！「応答メッセージ」と「AI応答メッセージ」とは｜LINE for Business @<href>{https://www.linebiz.com/jp/column/technique/20191128/}]

一方、AI応答メッセージはもう少し融通が利いて、ユーザーから送られたメッセージの内容をAIが判別して、適切なメッセージで自動で返信してくれます。たとえば飲食店なら、営業時間、住所、Wi-Fi、コンセント、駐車場、喫煙可否など、質問が想定されることについてそれぞれ事前に返信メッセージを設定しておくことで、単語が完全に一致しなくてもよしなに回答してくれます。たとえば「Wi-Fi」に対して「申し訳ありませんがWi-Fiはご利用いただけません」という回答をオンにしておくと、「Wi-Fiってありますか？」のようなメッセージだけに限らず、「ネットって使えたりする？」「無線ってありますか？」「無料のわいふぁいって使える？」といったメッセージでもきちんとその回答が返ってきます。

応答メッセージとAI応答メッセージは、どちらか片方だけ使うこともできますし、キーワードに完全一致したら応答メッセージを返して、そうでない場合はAI応答メッセージを返す、というように両方使うこともできます。

さらに方法2と方法3を併用することも可能です。LINE Official Account Managerや管理アプリで営業時間を設定しておくことで、営業時間内は中の人が手打ちのチャットで応答して、営業時間外は自動応答のメッセージに任せる、というような運用ができます。

=== 方法4. Messaging APIで返信する

4つめはMessaging APIで返信する、という方法です。Messaging APIでは、この「ユーザー起点のコミュニケーション」に気づく方法として、Webhookというものが用意されており、このWebhookをボットサーバーで受け止めることでボットから返信ができます。ではWebhookとはいったいどんなものなのでしょう？

=== Webhookとは

ユーザーが、LINE公式アカウントを友だち追加したり、ブロックしたり、LINE公式アカウントにメッセージを送ったりというように、何かしらの「イベント」を起こすと、LINEプラットフォームからボットサーバーに対して、Webhookが送られます。LINEプラットフォームから送られてくるWebhookを受け止めるために、LINE公式アカウントを運営するあなたは、自分でこのボットサーバーを用意する必要があります。（@<img>{webhook}）

//image[webhook][ユーザーがメッセージを送るとボットサーバーにWebhookが飛んでくる][scale=0.8]{
//}

通常、私たちはブラウザでショッピングサイトのマイページを開いて、住所を入力して送信ボタンを押すことで、ウェブサーバーに「住所情報をこれに変更にしてくれ！」とリクエストを投げ、リクエストを受けたウェブサーバーが諸々の処理をしてから「はい。住所変更終わりましたよ」と変更完了ページをレスポンスで返してくれたりします。このときは、ウェブサーバー側が「サーバー」で、自分やブラウザ側が「クライアント」です。

しかしWebhookにおいてはこれが逆転します。LINEプラットフォームから「ユーザーがこんなメッセージを送ってきたよ！Webhookを受け取って！」とリクエストが飛んでくるので、あなたは用意したボットサーバーでそれを受け取って、「ありがとう！Webhookちゃんと受け取ったよ！ステータスコード200！」というレスポンスを返さなければいけません。Webhookを投げてくるLINEプラットフォームが「クライアント」で、あなたの用意するボットサーバーが「サーバー」なのです。

私たちはクライアントの立場は頻繁に経験していますが、サーバーの立場になる経験はあまりないのでなんだか不思議な感じがしますね。自分が「ボットサーバーを用意する側」であり、「Webhookを受け取ってレスポンスを返す側」だ、と言われてもまだあんまりピンとこないかもしれません。この説明だけで今すぐにWebhookを完璧に理解できなくても大丈夫です。手を動かしてボットサーバーを用意し、実際にWebhookを受け取ってみましょう。

===[column] 【コラム】LINE公式アカウントの「既読」はいつ付くのか？

普通の友だちとのLINEのメッセージは、相手がトークルームを開いてメッセージを見ることで「既読」がつきます。ではLINE公式アカウントの場合は、「既読」はいつ付くのでしょう？

LINE Official Account Managerや管理アプリの応答設定に［チャット］と［Webhook］という設定項目があります。この［チャット］をオンにしていると、中の人がチャットの画面でメッセージを確認するまでは、LINE公式アカウント側でメッセージを読んだことを示す「既読」マークがつきません。逆にこの［チャット］をオフにしていると、メッセージが送られた瞬間に自動的に「既読」がつきます。

Messaging APIを使ってLINE公式アカウントから自動応答しているのに、なぜか「既読」マークが付かない！というときは、うっかり応答設定で［チャット］をオンにしないか確認してみてください。応答設定で「Webhookだけをオンにしている」だと自動で既読が付きますが、「チャットだけをオンにしている」もしくは「チャットとWebhookの両方をオンにしている」状態だと、チャットの画面でメッセージを確認するまで既読が付きません。

［チャット］も［Webhook］も両方オンにして併用したいけど、チャット画面で確認したときではなく自動で既読を付けたい、という場合は「既読API@<fn>{mark-as-read}」というAPIを使うことで任意のタイミングで既読が付けられます。ただ残念ながら既読APIは法人ユーザー限定のオプション機能です。

===[/column]

//footnote[mark-as-read][既読API | LINE Developers @<href>{https://developers.line.biz/ja/docs/partner-docs/mark-as-read/}]

== オウム返しするチャットボットを作ってみよう

それではメッセージをWebhookで受け取って、ボットから自動返信する一連の流れを理解するため、先ずは一番簡単な「オウム返しするチャットボット」を作ってみましょう。

==={prepare-messaging-api-sdk} Messaging APIのSDKを準備する

Messaging APIでは、開発をサポートするSDKがJava、PHP、Go、Perl、Ruby、Python、Node.jsで用意@<fn>{messaging-api-sdk}されています。SDKはSoftware Development Kitの略で、名前のとおり開発に必要なライブラリが詰まった工作キットのようなものです。たとえば料理でも、材料を揃えて野菜の皮を剥くところからやるととても大変ですが、下ごしらえの済んだ材料とレシピがひとまとめになっているミールキットを使えば、誰でも短時間で失敗もなく美味しい食事が作れます。それと同じで、開発においてもSDKが用意されていたら、そのSDKを使うことで色々とラクができます。

//footnote[messaging-api-sdk][LINE Messaging API SDK | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/line-bot-sdk/}]

今回はPythonのSDKを使ってコードを書いていきます。

 * LINE Messaging API SDK for Python
 ** @<href>{https://github.com/line/line-bot-sdk-python}

それではSDKを使うための準備をしていきましょう。

==== Windowsの場合

@<hd>{article02|curl}で使用したWSLを再び起動して、以下のコマンドを順番にたたいていきます。@<ttb>{$}はWSLのプロンプトを表していますので入力しないでください。

先ずはcdコマンドでホームディレクトリ@<fn>{dir}に移動して、mkdirコマンドでpython@<fn>{python-dir}というディレクトリを作ります。lsコマンドで確認して「python」と表示されたら、問題なくpythonディレクトリが作成できていますので、作成したpythonディレクトリの中にcdコマンドで移動してください。（@<img>{get-sdk-1}）

//footnote[dir][前述のとおりWSLはWindows上で動くLinux環境であり、Linuxではフォルダのことをディレクトリと呼びます。なので、ここではディレクトリと書いてあったら「ああ、フォルダのことだな」と思ってください。]
//footnote[python-dir][このディレクトリ名は必ずpythonにしてください。ディレクトリ名をpython以外にするとこの後の手順で正常に動きません。]

//cmd{
$ cd
$ mkdir python
$ ls
$ cd python
//}

//image[get-sdk-1][pythonディレクトリを作ってその中に移動する][scale=1]{
//}

続いて、SDKをパソコンの中に取ってくるためにpipコマンドが使いたいので、aptコマンドでpipコマンドを連れてきます。@<ttb>{sudo apt update}をたたくとパスワードを聞かれるので、パソコンを起動したときに入力するのと同じパスワードを入力してEnterを押してください。@<ttb>{sudo apt install python3-pip}をたたくと、メッセージがだだーっと流れた後に@<ttb>{Do you want to continue? [Y/n]}と聞かれるので、Yを入力してEnterを押します。

//cmd{
$ sudo apt update
$ sudo apt install python3-pip
//}

いよいよpipコマンドでSDKをパソコンの中に取得してきます。SDKを取ってきたら、lsコマンドでpythonディレクトリの中身を確認してみましょう。中身がなんだかたくさん入っていれば成功です。（@<img>{get-sdk-2}）

//cmd{
$ pip install line-bot-sdk -t . --no-user
$ ls
//}

//image[get-sdk-2][取ってきたSDKがpythonディレクトリの中にみっしり入っている][scale=1]{
//}

取ってきたSDKをぎゅっとZIPに固めたいので、cdコマンドで1つの上のディレクトリに移動しましょう。そしてaptコマンドでzipコマンドを連れてきます。@<ttb>{sudo apt install zip}をたたくと、メッセージがだだーっと流れた後に@<ttb>{Do you want to continue? [Y/n]}と聞かれるので、Yを入力してEnterを押してください。

//cmd{
$ cd ..
$ sudo apt install zip
//}

それではzipコマンドでpythonディレクトリをぎゅっとZIPに固めましょう。lsコマンドでpython.zipとpythonディレクトリが確認できたら、これでSDKは準備完了です。（@<img>{get-sdk-3}）

//cmd{
$ zip -r python.zip python
$ ls
//}

//image[get-sdk-3][zipコマンドでpythonディレクトリをZIPに固める][scale=1]{
//}

最後に@<ttb>{explorer.exe .}をたたくと、WSLで見ていたディレクトリがエクスプローラで表示されます。（@<img>{get-sdk-4}、@<img>{get-sdk-5}）

//cmd{
$ explorer.exe .
//}

//image[get-sdk-4][「explorer.exe .」をたたく][scale=1]{
//}

//image[get-sdk-5][するとエクスプローラでpython.zipのあるフォルダが表示される][scale=0.8]{
//}

作成したpython.zipはこの後すぐに使うので、デスクトップにコピーしておきましょう。（@<img>{copy-to-desktop}）

//image[copy-to-desktop][python.zipはデスクトップにコピーしておく][scale=1]{
//}

これでMessaging APIのSDKが準備できました。

==== Macの場合

Macの場合は、デフォルトでpipコマンドやzipコマンドが入っているので、Windowsの手順から@<ttb>{sudo apt install ○○}というコマンドを除いて同様に実行してください。

=== AWS LambdaとAPI Gatewayでボットサーバーを作る

今回はWebhookを受け取ってレスポンスを返すボットサーバーとして、AWSのサーバーレスサービス、AWS LambdaとAPI Gatewayを使用します。

AWSを初めて使用する場合、AWSアカウントを作成してから1年間は利用料が無料となります。ただし無料利用枠の範囲は決まっており、何をどれだけ使っても無料という訳ではありません。どのサービスをどれくらい無料で使えるのか？は「AWS無料利用枠」のページに記載されていますので、そちらを参照してください。AWSアカウントを持っていない場合は、同じ「AWS無料利用枠」のページにある［無料アカウントの作成］から作成してください。@<fn>{create-aws-account}（@<img>{awsFree}）

 * AWS無料利用枠
 ** @<href>{https://aws.amazon.com/jp/free/}

//image[awsFree][AWS無料利用枠][scale=0.8]{
//}

//footnote[create-aws-account][なおAWSアカウントの作成の詳しい手順は「DNSをはじめよう」という書籍で、またAWSとは何かについての説明や、無料利用枠の範囲、利用金額が一定額を超えたらアラートが飛ぶようにする設定などは「AWSをはじめよう」という書籍で詳しく紹介しています。もしAWSアカウントの作成や設定に不安がある場合は、そちらを参考にしてください。 @<href>{https://mochikoastech.booth.pm/}]

それでは早速、AWSのマネジメントコンソールを開いて、上部の検索窓で@<ttb>{lambda}と検索し、AWS Lambdaを開きます。（@<img>{search-lambda}）

 * AWSマネジメントコンソール
 ** @<href>{https://console.aws.amazon.com/}

//image[search-lambda][検索窓からLambdaを開く][scale=0.8]{
//}

==== Messaging API SDKのレイヤーを作成する

AWS Lambdaを開いたら、左メニューの［レイヤー］から、［レイヤーの作成］をクリックします。（@<img>{create-layer}）

//image[create-layer][［レイヤーの作成］をクリック][scale=0.8]{
//}

「名前」と「説明」は次のように入力します。（@<table>{layer-settings}）

//table[layer-settings][レイヤー設定]{
名前	Messaging-API-SDK-for-python
説明	Messaging API SDK for python
アップロード方法	.zip ファイルをアップロード
アップロードするファイル	@<hd>{article02|prepare-messaging-api-sdk}で用意したpython.zip
互換性のあるアーキテクチャ	x86_64にチェックを入れる
互換性のあるランタイム	Python 3.10を選択
ライセンス	https://github.com/line/line-bot-sdk-python/blob/master/LICENSE
//}

［アップロード］をクリックしたら、@<hd>{article02|prepare-messaging-api-sdk}で準備しておいた、デスクトップのpython.zipを選択し、アップロードしてください。（@<img>{select-python-zip}）

//image[select-python-zip][デスクトップにあるpython.zipを選択してアップロード][scale=0.8]{
//}

必要事項を入力したら［作成］をクリックします。（@<img>{create-layer-2}）

//image[create-layer-2][必要事項を入力したら［作成］をクリックする][scale=0.8]{
//}

これでMessaging API SDKのレイヤーができました！（@<img>{create-layer-3}）

//image[create-layer-3][レイヤーができた！][scale=0.8]{
//}

==== Lambda関数を作成する

次はLambda関数を作成しますので、左メニューの［関数］から［関数の作成］を開いてください。（@<img>{create-lambda}）

//image[create-lambda][［関数の作成］をクリックする][scale=0.8]{
//}

関数の作成に必要な情報は、次のように入力します。（@<table>{create-app}）

//table[create-app][関数の作成]{
関数名	Bot-Server-on-Lambda
ランタイム	Python 3.10
アーキテクチャ	x86_64
その他の設定	すべてデフォルトのまま
//}

必要事項を入力したら［関数の作成］をクリックします。（@<img>{create-lambda-2}）

//image[create-lambda-2][［関数の作成］をクリックする][scale=0.8]{
//}

これでLambda関数ができました！続いて、このLambda関数に、先に作っておいたMessaging API SDKのレイヤーを追加したいので、［Layers］をクリックします。（@<img>{create-lambda-3}）

//image[create-lambda-3][Lambda関数ができたら［Layers］をクリックする][scale=0.8]{
//}

［レイヤーの追加］をクリックします。（@<img>{create-lambda-4}）

//image[create-lambda-4][［レイヤーの追加］をクリックする][scale=0.8]{
//}

レイヤーは次のように選択します。（@<table>{select-layer}）

//table[select-layer][レイヤーを選択]{
レイヤーソース	カスタムレイヤー
カスタムレイヤー	Messaging-API-SDK-for-python
バージョン	1
//}

使用するレイヤーを選択したら［追加］をクリックします。（@<img>{create-lambda-5}）

//image[create-lambda-5][［追加］をクリックする][scale=0.8]{
//}

［Layers］の後ろの数字が@<ttb>{(0)}から@<ttb>{(1)}になりました。これでLambda関数にMessaging API SDKのレイヤーが追加できました！こうしてレイヤーを追加することで、Lambda関数でMessaging API SDKが使えるようになります。（@<img>{create-lambda-6}）

//image[create-lambda-6][Messaging API SDKのレイヤーが追加できた！][scale=0.8]{
//}

次はAPI Gatewayを作成しますので、［トリガーを追加］を開いてください。

===={create-api-gateway} API Gatewayを作成する

［ソースを選択］で［API Gateway］を選択します。（@<img>{create-api-gateway}）
\^^^^^^^^^
//image[create-api-gateway][［API Gateway］を選択する][scale=0.8]{
//}

トリガーの設定は次のようにします。（@<table>{trigger-settings}）

//table[trigger-settings][トリガーの設定]{
インテント	新規APIを作成
APIタイプ	HTTP API
セキュリティ	開く
その他の設定	すべてデフォルトのまま
//}

トリガーの設定を選択したら［追加］をクリックします。（@<img>{create-api-gateway-2}）

//image[create-api-gateway-2][［追加］をクリックする][scale=0.8]{
//}

これでAPI Gatewayが作成できました！（@<img>{create-api-gateway-3}）

//image[create-api-gateway-3][API Gatewayができた！][scale=0.8]{
//}

［トリガー］の中にある［APIエンドポイント］のURLをブラウザで開くと、AWS Lambdaから［"Hello from Lambda!"］というレスポンスが返ってきます。（@<img>{create-api-gateway-4}）

//image[create-api-gateway-4][［APIエンドポイント］のURLを開くとレスポンスが返ってきた][scale=0.8]{
//}

この［APIエンドポイント］のURLは、後でWebhookを受け止めるボットサーバーの「Webhook URL」として使用します。チャネルアクセストークンやチャネルシークレットと同様に、パソコンのメモ帳にしっかりメモしておいてください。

==== Lambda関数で動かすpythonのコードを書く

ブラウザで［APIエンドポイント］のURLを開いたとき、［"Hello from Lambda!"］というレスポンスが返ってきたのは、Lambda関数の［コード］タブのコードソースに次のようなコードが書いてあったからです。（@<list>{default-source-code-1}）

//listnum[default-source-code-1][Lambda関数のデフォルトのコード][python]{
import json

def lambda_handler(event, context):
    # TODO implement
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
//}

このデフォルトのコードは、リクエストが来たら、ステータスコード200と共に「Hello from Lambda!」というメッセージを含むJSONを返すようになっています。（@<img>{parrot-bot}）

//image[parrot-bot][ステータスコード200とJSONを返すコード][scale=1]{
//}

このコードを、次のようにWebhookを受け取ってオウム返しするコード@<fn>{parrot-bot-url}に書き直してみましょう。（@<list>{parrot-source-code-1}）

//footnote[parrot-bot-url][このコードはGitHubで公開されている本書のリポジトリからもダウンロードできます。 @<href>{https://github.com/mochikoAsTech/startLINEBot/blob/master/articles/parrotbot.py}]

//listnum[parrot-source-code-1][Webhookでメッセージを受け取ってオウム返しするコード][python]{
import json
import logging
import os
import sys

from linebot import LineBotApi, WebhookHandler
from linebot.exceptions import InvalidSignatureError, LineBotApiError
from linebot.models import MessageEvent, TextMessage, TextSendMessage

# INFOレベル以上のログメッセージを拾うように設定する
logger = logging.getLogger()
logger.setLevel(logging.INFO)

# 環境変数からMessaging APIのチャネルアクセストークンとチャネルシークレットを取得する
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')

# それぞれ環境変数に登録されていないとエラー
if CHANNEL_ACCESS_TOKEN is None:
    logger.error(
        'LINE_CHANNEL_ACCESS_TOKEN is not defined as environmental variables.')
    sys.exit(1)
if CHANNEL_SECRET is None:
    logger.error(
        'LINE_CHANNEL_SECRET is not defined as environmental variables.')
    sys.exit(1)

line_bot_api = LineBotApi(CHANNEL_ACCESS_TOKEN)
webhook_handler = WebhookHandler(CHANNEL_SECRET)


@webhook_handler.add(MessageEvent, message=TextMessage)
def handle_message(event):

    # 応答トークンを使って回答を応答メッセージで送る
    line_bot_api.reply_message(
        event.reply_token, TextSendMessage(text=event.message.text))


def lambda_handler(event, context):

    # リクエストヘッダーにx-line-signatureがあることを確認
    if 'x-line-signature' in event['headers']:
        signature = event['headers']['x-line-signature']

    body = event['body']
    # 受け取ったWebhookのJSONを目視確認できるようにINFOでログに吐く
    logger.info(body)

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
//}

コードを直したら、［Deploy］を押してデプロイ（修正後のコードを反映）します。（@<img>{parrot-bot-2}）

//image[parrot-bot-2][［Deploy］を押して修正後のコードを反映する][scale=0.8]{
//}

［関数 Bot-Server-on-Lambda が正常に更新されました。］と表示されたらデプロイ完了です。（@<img>{parrot-bot-3}）

//image[parrot-bot-3][デプロイ完了][scale=0.8]{
//}

==== 環境変数を設定する

いまデプロイしたコードを実際に動かすには、Messaging APIのチャネルアクセストークンとチャネルシークレットが必要です。どちらもソースコードには直接書かず、環境変数として設定しておいて、コードからは@<ttb>{CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')}というように環境変数を参照する形にしています。

Lambda関数の［設定］タブから［環境変数］を開いて、［編集］をクリックします。（@<img>{parrot-bot-4}）

//image[parrot-bot-4][［環境変数］の［編集］をクリックする][scale=0.8]{
//}

［環境変数の追加］を2回クリックして、［キー］と［値］を次のように設定します。チャネルアクセストークンとチャネルシークレットは、@<hd>{article02|issue-token}でコピーしてメモ帳に保存してあるはずです。（@<table>{set-env}）

//table[set-env][環境変数の編集]{
キー	値
--------------------
CHANNEL_ACCESS_TOKEN	チャネルアクセストークン
CHANNEL_SECRET	チャネルシークレット
//}

環境変数を編集したら［保存］をクリックします。（@<img>{parrot-bot-5}）

//image[parrot-bot-5][環境変数を編集したら［保存］をクリックする][scale=0.8]{
//}

［関数 Bot-Server-on-Lambda が正常に更新されました。］と表示されたら環境変数の設定完了です。（@<img>{parrot-bot-6}）

//image[parrot-bot-6][環境変数の設定完了][scale=0.8]{
//}

これでボットサーバーの準備は万端です。LINE Developersコンソールに戻って、ボットサーバーのURLを「Webhook URL」に設定しましょう。

=== Webhook URLを設定する

LINE Developersコンソール@<fn>{console}を開いて、Messaging APIチャネルの［Messaging API設定］タブにある［Webhook設定］の［Webhook URL］を登録します。［編集］をクリックしてください。（@<img>{webhook-url}）

//footnote[console][@<href>{https://developers.line.biz/console/}]

//image[webhook-url][［Webhook URL］の［編集］をクリックする][scale=0.8]{
//}

@<hd>{article02|create-api-gateway}でメモしておいたAPIエンドポイントのURLを貼り付けて、［更新］をクリックしてください。（@<img>{webhook-url-2}）

//image[webhook-url-2][APIエンドポイントのURLを貼り付けて［更新］をクリックする][scale=0.8]{
//}

Webhook URLを設定したら、［検証］を押してボットサーバーとの動作検証をしてみましょう。（@<img>{webhook-url-3}）

//image[webhook-url-3][［検証］を押す][scale=0.8]{
//}

［成功］と返ってきたら、LINEプラットフォームからのWebhookをボットサーバーが受け取って、ちゃんとステータスコード200を返してきています。［OK］を押してポップアップを閉じておきましょう。やりましたね！おめでとうございます。（@<img>{webhook-url-4}）

//image[webhook-url-4][［成功］と返ってきたら［OK］をクリックする][scale=0.8]{
//}

ボットサーバーがWebhookをきちんと受け取れなかったときに備えて、［Webhook URL］の少し下にある［エラーの統計情報］@<fn>{error}をオンにしておきましょう。この［エラーの統計情報］をオンにしておくと、もしボットサーバーがWebhookの受け取りに失敗した場合に、LINE Developersコンソール上でそのログが確認できます。Webhook URLの［検証］を押してエラーが返ってきたときや、友だちがメッセージを送ってきたのにLINE公式アカウントからきちんと返信が送れていない場合は、ボットサーバーのログ@<fn>{logs}と共に、［統計情報］タブでエラーの統計情報も確認しましょう。（@<img>{webhook-error}）

//footnote[error][Webhookの送信におけるエラーの統計情報を確認する | LINE Developers@<href>{https://developers.line.biz/ja/docs/messaging-api/receiving-messages/#error-statistics-aggregation}]
//footnote[logs][ボットサーバーのログについては、@<hd>{article02|cloudwatch-logs}で後述します。]

//image[webhook-error][［エラーの統計情報］をオンにしておく][scale=0.8]{
//}

［検証］を押して［成功］と返ってきたら、ボットサーバーは問題なく動いているようなので、同じ［Messaging API設定］タブにある［応答メッセージ］の［編集］からLINE Official Account Managerを開きます。（@<img>{webhook-url-5}）

//image[webhook-url-5][［応答メッセージ］の［編集］からLINE Official Account Managerを開く][scale=0.8]{
//}

ユーザーがメッセージを送ってきたら、今後はWebhookを受け取ったボットサーバーから応答したいので、［応答設定］の［Webhook］をオンにして、代わりに［応答メッセージ］をオフにしてください。（@<img>{webhook-url-6}）

//image[webhook-url-6][［成功］と返ってきたら［OK］をクリックする][scale=0.8]{
//}

これでWebhookの設定は完了です。LINEプラットフォームからのWebhookが、AWS Lambdaで用意したボットサーバーに向かって飛んでくるようになりました。

==={greeting} 友だち追加されたときのあいさつメッセージを併用する

友だち追加されたときに、自動で任意のメッセージを送ることができる「あいさつメッセージ」も、LINE Official Account Managerの［応答設定］でオン、オフの設定ができます。このあいさつメッセージは、Webhookと併用することが可能です。本書では、友だち追加されたときの応答は「あいさつメッセージ」で行い、メッセージが届いたときの応答はボットサーバーから行いたいので、あいさつメッセージはオンのままで構いません。

なお友だち追加されたときにWebhookで飛んでくるフォローイベント@<fn>{follow}を用いると、「あいさつメッセージ」と同等の処理をボットサーバーでも実現できます。

//footnote[follow][フォローイベント | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#follow-event}]

==={cloudwatch-logs} LINEプラットフォームから飛んできたWebhookを目視確認する

先ほど、LINE DevelopersコンソールでWebhook URLの［検証］を押したとき、LINEプラットフォームからボットサーバーに飛んできたWebhookを目視確認してみましょう。ボットサーバーのログは、AWSのCloudWatchで確認できます。AWSのマネジメントコンソールを開いて、上部の検索窓で@<ttb>{cloudwatch}と検索し、CloudWatchを開きます。（@<img>{cloudwatch}）

//image[cloudwatch][検索窓からCloudWatchを開く][scale=0.8]{
//}

CloudWatchを開いたら、左メニューの［ロググループ］から［/aws/lambda/Bot-Server-on-Lambda］を開きます。（@<img>{cloudwatch-1}）

//image[cloudwatch-1][［/aws/lambda/Bot-Server-on-Lambda］を開く][scale=0.8]{
//}

いちばん上にある最新のリクエストのログストリームを開きます。（@<img>{cloudwatch-2}）

//image[cloudwatch-2][いちばん上にあるログストリームを開く][scale=0.8]{
//}

@<ttb>{[INFO]}からはじまる行を開いて確認します。すると、Webhookを受け取ってオウム返しするコード（@<list>{parrot-source-code-1}）の48行目で出力しておいたログが確認できます。これがLINEプラットフォームから届いたWebhookのJSONです。（@<img>{cloudwatch-3}）

//image[cloudwatch-3][LINEプラットフォームから届いたWebhookのJSONが確認できる][scale=0.8]{
//}

//listnum[webhook-json][［検証］を押したときに飛んできたWebhookのJSON][json]{
{
    "destination": "U61（中略）a19",
    "events": []
}
//}

@<ttb>{destination}には、その「destination（お届け先）」という名前のとおり、LINEプラットフォームがWebhookを渡す相手、つまりLINE公式アカウント自身のユーザーIDが入っています。

今回は動作検証だけだったので@<ttb>{events}の中身は空配列でしたが、友だち追加されたときや、友だちからメッセージが届いたときは、ここにメッセージイベントやフォローイベントなどが入ってきます。@<ttb>{events}の中に入ってくるWebhookイベントオブジェクトについては、公式ドキュメントのAPIリファレンス@<fn>{event-objects}を参照してください。

//footnote[event-objects][Webhookイベントオブジェクト | Messaging APIリファレンス | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#webhook-event-objects}]

=== LINE公式アカウントに話しかけてオウム返しを確認しよう

それではLINEでLINE公式アカウントに話しかけて、まったく同じメッセージがオウム返しされるか確認してみましょう。（@<img>{parrot-reply}）

//image[parrot-reply][メッセージを送ったらLINE公式アカウントがオウム返ししてくれた][scale=0.8]{
//}

おめでとうございます！オウム返ししてくれるLINE Botの完成です。

===[column] 【コラム】これは本当にLINEプラットフォームから来たWebhook？

ボットサーバーにLINEプラットフォームからWebhookが届いたら、その内容に応じて返信を送ったり、何か処理をしたりします。

このとき、届いたリクエストが本当にLINEプラットフォームから届いたWebhookなのか、それともLINEプラットフォームを装った第三者からの攻撃なのか、どうやって判別すればよいのでしょう？

アクセス元のIPアドレスが分かれば、IPアドレスで制限をかけることで、LINEプラットフォーム以外からのアクセスを遮断できますが、残念ながらLINEプラットフォームはIPアドレスのレンジを開示していません。@<fn>{ip-addr}代わりに推奨されているのが「署名の検証」という方法です。

LINEプラットフォームから届くWebhookには、そのリクエストヘッダーに必ず@<ttb>{x-line-signature}という署名が含まれています。Messaging APIチャネルのチャネルシークレットを秘密鍵として扱い、届いたWebhookのリクエストボディのダイジェスト値を取得し、さらにそのダイジェスト値をチャネルシークレットを用いてBase64エンコードした値と、リクエストヘッダーの@<ttb>{x-line-signature}の署名が一致することを確認できれば、これが本当にLINEプラットフォームから届いたWebhookである、というセキュリティの担保ができます。

この検証をしないで、無条件に「テキストメッセージのWebhookイベントが届いたらユーザーに返信する」のような処理をしていると、ボットサーバーに偽のWebhookを投げ続けることで、LINE Botを介して特定のユーザーに大量のメッセージを送りつける攻撃が可能になってしまいます。

署名検証の各言語ごとのコードサンプルは、公式ドキュメントの「署名を検証する@<fn>{signature}」にありますし、SDKを用いることで簡単に検証できます。

Webhookを受け取ってオウム返しするコード（@<list>{parrot-source-code-1}）では、リクエストヘッダーに含まれていた@<ttb>{x-line-signature}を44行目で@<ttb>{signature}に詰めて、51行目で署名検証しています。署名検証した結果、もしLINEプラットフォームを装った第三者からのリクエストだったら、52行目からのエラー処理でステータスコード400を返して、返信の処理は行わないようになっています。

===[/column]

//footnote[ip-addr][Webook | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#webhooks}]
//footnote[signature][署名を検証する | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#signature-validation}]

== ChatGPTのAPIを使ったAIチャットボットを作ってみよう

LINE公式アカウントにメッセージを送って、無事にオウム返しのチャットボットが動いてくれるとうれしいですね！うれしいものの、「オウム返しされたけど……だからなに？」という気持ちにもなるので、今度はChatGPTのAPIを使って、LINE公式アカウントの中身をちゃんと役に立つAIチャットボットに作り変えてみましょう。

=== ChatGPTとGPT-3.5とは

ChatGPTはOpenAIが提供している対話型のウェブサービスです。OpenAIのアカウントを作れば、誰でも利用できます。（@<img>{chat-gpt}）

 * ChatGPT - OpenAI
 ** @<href>{https://chat.openai.com/}

//image[chat-gpt][ChatGPTでChatGPTのことを質問している様子][scale=1]{
//}

このChatGPTの裏側で応答を生成している言語モデルがGPT-3.5です。OpenAIが提供するOpenAI APIを使って質問を投げ、GPT-3.5からの回答を取得することも可能です。

それでは先ほどのオウム返しボットを少し作り変えて、ユーザーがLINEで質問を送るとGPT-3.5がその文脈に基づいて回答を生成し、その回答がLINE公式アカウントからのメッセージとして返ってくる、というAIチャットボットにしていきましょう。@<fn>{chatgpt}

//footnote[chatgpt][本書を書いている最中に「ChatGPTだー！」「GPT-3.5だー！」「いやGPT-4だー！」とインターネットがお祭り騒ぎになったので、なんとか間に合わせるために寝不足で吐きそうになりながら動作検証をして、この「ChatGPTのAPIを使ったAIチャットボットを作る」という節を書き足しました。だってみんな、いまAIチャットボット作れる本が出たら絶対に嬉しいと思ったから！]

==={issue-secret-key} OpenAIに登録してシークレットキーを取得する

Messaging APIを使うにはチャネルアクセストークンが必要だったように、OpenAI APIを使うには、OpenAI APIのサイトでアカウントを作ってシークレットキーを取得する必要があります。

それではOpenAI APIのサイトにアクセスして、右上の［Sign up］を開いてください。（@<img>{openai-api-site}）

 * OpenAI API
 * @<href>{https://platform.openai.com/overview}

//image[openai-api-site][右上の［Sign up］を開く][scale=0.8]{
//}

［Create your account］と表示されたら、メールアドレスを入力して［Continue］をクリックします。（@<img>{openai-account-1}）

//image[openai-account-1][メールアドレスを入力して［Continue］をクリックする][scale=0.8]{
//}

続いてパスワードを入力して、［Continue］をクリックします。（@<img>{openai-account-2}）

//image[openai-account-2][パスワードを入力して［Continue］をクリックする][scale=0.8]{
//}

［Verify your email］と表示されます。（@<img>{openai-account-3}）

//image[openai-account-3][［Verify your email］と表示されたらメールを確認しよう][scale=0.8]{
//}

すると、入力したメールアドレス宛てに［OpenAI - Verify your email］という件名のメールが届きます。［Verify email address］をクリックしてください。（@<img>{openai-account-4}）

//image[openai-account-4][届いたメールの［Verify email address］をクリックする][scale=0.8]{
//}

メールアドレスの確認ができたら、［Tell us about you］と表示されます。苗字と名前、そして生年月日を入力して、［Continue］をクリックします。（@<img>{openai-account-5}）

//image[openai-account-5][苗字と名前と生年月日を入力して［Continue］をクリックする][scale=0.8]{
//}

［Verify your phone number］と表示されたら、携帯電話の電話番号を入力します。プラス記号と国番号の81からはじまる国際的な電話番号の形式なので、あなたの電話番号が「080-0123-4567」なら「8012345678」と入力してください。入力したら［Send code］をクリックします。（@<img>{openai-account-6}）

//image[openai-account-6][電話番号を入力して［Send code］をクリックする][scale=0.8]{
//}

すると入力した電話番号のスマートフォン宛てに、［あなたのOpenAI API 認証コード］というSMSが届きます。（@<img>{openai-account-7}）

//image[openai-account-7][［あなたのOpenAI API 認証コード］][scale=0.4]{
//}

SMSに書いてある6桁の認証コードを、［Enter code］と表示された画面で入力してください。（@<img>{openai-account-8}）

//image[openai-account-8][SMSで届いた6桁の認証コードを［Enter code］の画面で入力する][scale=0.8]{
//}

右上のアイコンをクリックして自分のメールアドレスが表示されていたら、OpenAI APIのアカウント登録は完了です。［VIEW API keys］を開いてしてください。（@<img>{openai-account-9}）

//image[openai-account-9][OpenAI APIのアカウント登録が完了したら［VIEW API keys］を開く][scale=0.8]{
//}

OpenAI APIをたたくためのシークレットキーはまだ存在していないので、［Create new secret key］をクリックして作成しましょう。（@<img>{openai-account-10}）

//image[openai-account-10][［Create new secret key］をクリックする][scale=0.8]{
//}

シークレットキーの［Name］は任意入力ですが、何の用途で作った鍵なのか後で分からなくなってしまわないように、［OpenAI API secret key for LINE Bot］と書いておきましょう。［Create secret key］をクリックします。（@<img>{openai-account-11}）

//image[openai-account-11][［Create secret key］をクリックする][scale=0.8]{
//}

シークレットキーが作成されました。このシークレットキーはこの画面でコピーしておかないと、以降二度と表示されません。もし無くしたらシークレットキーを再び作成することになります。コピーボタンを押して、チャネルアクセストークンやチャネルシークレットと同様に、パソコンのメモ帳にしっかりメモしておいてください。メモできたら［Done］をクリックして、ポップアップを閉じます。（@<img>{openai-account-12}）

//image[openai-account-12][シークレットキーは二度と表示されないのでしっかりメモしておこう][scale=0.8]{
//}

これでOpenAI APIをたたくためのシークレットキーが手に入りました。（@<img>{openai-account-13}）

//image[openai-account-13][シークレットキーが手に入った！][scale=0.8]{
//}

LINE Developersコンソールで取得したチャネルアクセストークンと同様に、このシークレットキーはOpenAI APIをたたくときに身分証のような役割を果たします。うっかりシークレットキーが載った画面をブログで公開したり、ソースコードに直接書いてGitHubにPushしたりしないように注意してください。

==={openai-api-curl} OpenAI APIに質問を投げて回答を取得する

@<hd>{article02|curl}でcurlコマンドを使ってMessaging APIをたたき、メッセージを送信したように、今度はcurlコマンドでOpenAI APIに質問を投げて回答を取得してみましょう。

再びWSLまたはターミナルを起動します。次のcurlコマンド（@<list>{openai-api-curl}）の3行目にある「シークレットキー」の部分を、OpenAI APIのシークレットキーに置き換えてください。シークレットキーは、ついさっき@<hd>{article02|issue-secret-key}でコピーしてメモ帳に保存しましたね。

//listnum[openai-api-curl][curlコマンドで質問の回答を取得する][sh]{
curl https://api.openai.com/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer シークレットキー" \
  -d '{
    "model": "gpt-3.5-turbo",
    "messages": [{"role": "user", "content": "技術書典ってなんですか？"}]
  }'
//}

チャネルアクセストークンを置き換えたら、curlコマンドをまるごとコピーしてWSLもしくはターミナルに貼り付けます。WSLの場合は、複数行をまとめて貼り付けると警告が出ますが、［強制的に貼り付け］を押します。（@<img>{openai-curl-1}）

//image[openai-curl-1][複数行の貼り付けに対する警告が出たら［強制的に貼り付け］を押す][scale=0.8]{
//}

貼り付けたらEnterを押して実行します。（@<img>{openai-curl-2}）

//image[openai-curl-2][貼り付けたらEnterを押して実行する][scale=0.8]{
//}

回答の生成には少し時間がかかりますが、少し立つとレスポンスが画面に出力されます。curlコマンドを使ってAPIをたたいた結果、レスポンスとして回答を含むJSONオブジェクトが返ってきたことが分かります。（@<img>{openai-curl-3}）

//image[openai-curl-3][回答を含むJSONが返ってきた][scale=0.8]{
//}

リクエストで指定した@<ttb>{role}や@<ttb>{content}、返ってきたレスポンスの値がそれぞれ何を表しているのかは、OpenAI APIのAPIリファレンスを参照してください。

 * Create chat completion | API Reference - OpenAI API
 ** @<href>{https://platform.openai.com/docs/api-reference/chat/create}

curlコマンドでOpenAI APIに質問を投げて、回答を取得できました。「APIをたたく」ことに少し慣れてきましたか？

ちなみに2023年5月現在、OpenAI APIはアカウントを作ってから最初の3ヶ月は5ドル分まで無料@<fn>{openai-free}で使えるようです。自分が既に無料枠をどれくらい使ったのかは、OpenAI APIのUsage@<fn>{openai-free-2}で確認できます。（@<img>{openai-usage}）

//footnote[openai-free][Pricing @<href>{https://openai.com/pricing}]
//footnote[openai-free-2][Usage - OpenAI API@<href>{https://platform.openai.com/account/usage}]

//image[openai-usage][無料枠をどれくらい使ったのかはUsageで確認しよう][scale=0.8]{
//}

では続いて、OpenAI APIのSDKの準備をしていきましょう。

==={prepare-openai-api-sdk} OpenAI APIのSDKを準備する

先ほどのMessaging APIのSDKと同じように、OpenAI APIも公式がPythonとNode.jsでSDKを用意してくれています。AWS Lambdaで使うために、OpenAI APIのpython.zipを作成しましょう。

 * Python library - OpenAI API
 ** @<href>{https://platform.openai.com/docs/libraries/python-library}

===={openai-win} Windowsの場合

@<hd>{article02|curl}で使用したWSLを再び起動して、以下のコマンドを順番にたたいていきます。@<ttb>{$}はプロンプトを表していますので入力しないでください。

先ずはcdコマンドでさきほどMessaging APIのSDKを準備したのと同じホームディレクトリに移動して、lsコマンドでpythonフォルダとpython.zipが残っていることを確認します。rmコマンドでpythonフォルダとpython.zipを削除したら、再びlsコマンドをたたいてもう無いことを確認します。（@<img>{rm-rf}）

//cmd{
$ cd
$ ls
$ rm -rf python python.zip
$ ls
//}

//image[rm-rf][残っていたpythonフォルダとpython.zipを削除する][scale=1]{
//}

そして再びmkdirコマンドでpython@<fn>{python-dir-2}というディレクトリを作ります。lsコマンドで確認して「python」と表示されたら、問題なくpythonディレクトリが作成できていますので、作成したpythonディレクトリの中にcdコマンドで移動してください。（@<img>{get-openai-sdk-1}）

//footnote[python-dir-2][このディレクトリ名は必ずpythonにしてください。ディレクトリ名をpython以外にするとこの後の手順で正常に動きません。]

//cmd{
$ mkdir python
$ ls
$ cd python
//}

//image[get-openai-sdk-1][pythonディレクトリを作ってその中に移動する][scale=1]{
//}

いよいよpipコマンドでSDKをパソコンの中に取得してきます。SDKを取ってきたら、lsコマンドでpythonディレクトリの中身を確認してみましょう。中身がなんだかたくさん入っていれば成功です。（@<img>{get-openai-sdk-2}）

//cmd{
$ pip install openai -t . --no-user
$ ls
//}

//image[get-openai-sdk-2][取ってきたSDKがpythonディレクトリの中にみっしり入っている][scale=1]{
//}

それではcdコマンドで1つの上のディレクトリに移動して、zipコマンドでpythonディレクトリをぎゅっとZIPに固めましょう。lsコマンドでpython.zipとpythonディレクトリが確認できればOKです。（@<img>{get-sdk-3}）

//cmd{
$ cd ..
$ zip -r python.zip python
$ ls
//}

//image[get-openai-sdk-3][zipコマンドでpythonディレクトリをZIPに固める][scale=1]{
//}

最後に@<ttb>{explorer.exe .}をたたくと、WSLで見ていたディレクトリがエクスプローラで表示されます。（@<img>{get-sdk-4}、@<img>{get-sdk-5}）

//cmd{
$ explorer.exe .
//}

//image[get-openai-sdk-4][「explorer.exe .」をたたく][scale=1]{
//}

//image[get-openai-sdk-5][するとエクスプローラでpython.zipのあるフォルダが表示される][scale=0.8]{
//}

作成したpython.zipはこの後すぐに使うので、デスクトップに［ファイルを置き換える］でコピーしておきましょう。（@<img>{copy-to-desktop-2}）

//image[copy-to-desktop-2][python.zipはデスクトップに［ファイルを置き換える］でコピーしておく][scale=0.8]{
//}

これでOpenAI APIのSDKが準備できました。

===={openai-mac} Macの場合

Macの場合は、デフォルトでpipコマンドやzipコマンドが入っているので、Windowsの手順から@<ttb>{sudo apt install ○○}というコマンドを除いて同様に実行してください。

=== OpenAI API SDKのレイヤーを作成する

先ほどのMessaging API SDKと同様に、OpenAI API SDKのレイヤーをAWS Lambdaに追加します。AWSのマネジメントコンソールからAWS Lambdaを開いたら、左メニューの［レイヤー］から、［レイヤーの作成］をクリックします。（@<img>{openai-create-layer}）

//image[openai-create-layer][［レイヤーの作成］をクリック][scale=0.8]{
//}

「名前」と「説明」は次のように入力します。（@<table>{openai-layer-settings}）

//table[openai-layer-settings][レイヤー設定]{
名前	OpenAI-API-SDK-for-python
説明	OpenAI API SDK for python
アップロード方法	.zip ファイルをアップロード
アップロードするファイル	@<hd>{article02|prepare-openai-api-sdk}で用意したpython.zip
互換性のあるアーキテクチャ	x86_64にチェックを入れる
互換性のあるランタイム	Python 3.10を選択
ライセンス	https://github.com/openai/openai-python/blob/main/LICENSE
//}

［アップロード］をクリックしたら、@<hd>{article02|prepare-openai-api-sdk}で準備しておいた、デスクトップのpython.zipを選択し、アップロードしてください。（@<img>{openai-select-python-zip}）

//image[openai-select-python-zip][デスクトップにあるpython.zipを選択してアップロード][scale=0.8]{
//}

必要事項を入力したら［作成］をクリックします。（@<img>{openai-create-layer-2}）

//image[openai-create-layer-2][必要事項を入力したら［作成］をクリックする][scale=0.8]{
//}

これでOpenAI API SDKのレイヤーができました！（@<img>{openai-create-layer-3}）

//image[openai-create-layer-3][レイヤーができた！][scale=0.8]{
//}

次は、作成したOpenAI API SDKのレイヤーをLambda関数から利用するための設定を行います。左メニューから［関数］を開いてください。

==== Lambda関数にレイヤーを追加する

Lambda関数の一覧で、［Bot-Server-on-Lambda］をクリックします。（@<img>{add-openai-layer-to-lambda}）

//image[add-openai-layer-to-lambda][レイヤーができた！][scale=0.8]{
//}

このLambda関数に、先に作っておいたMessaging API SDKのレイヤーを追加したいので、［Layers］をクリックします。（@<img>{add-openai-layer-to-lambda-2}）

//image[add-openai-layer-to-lambda-2][［Layers］をクリックする][scale=0.8]{
//}

［レイヤーの追加］をクリックします。（@<img>{add-openai-layer-to-lambda-3}）

//image[add-openai-layer-to-lambda-3][［レイヤーの追加］をクリックする][scale=0.8]{
//}

レイヤーは次のように選択します。（@<table>{select-openai-layer}）

//table[select-openai-layer][レイヤーを選択]{
レイヤーソース	カスタムレイヤー
カスタムレイヤー	OpenAI-API-SDK-for-python
バージョン	1
//}

使用するレイヤーを選択したら［追加］をクリックします。（@<img>{add-openai-layer-to-lambda-4}）

//image[add-openai-layer-to-lambda-4][［追加］をクリックする][scale=0.8]{
//}

［Layers］の後ろの数字が@<ttb>{(1)}から@<ttb>{(2)}になりました。これでLambda関数にOpenAI API SDKのレイヤーが追加できました！こうしてレイヤーを追加することで、Lambda関数でOpenAI API SDKが使えるようになります。（@<img>{add-openai-layer-to-lambda-5}）

//image[add-openai-layer-to-lambda-5][OpenAI API SDKのレイヤーが追加できた！][scale=0.8]{
//}

=== AWS LambdaのコードにChatGPTのAPIで質問の回答を取得する処理を追加する

ユーザーの質問に対して、AIチャットボットが自動で応答するようにコードを変更します。Lambda関数の［コード］タブのコードを、次のコード@<fn>{ai-chat-bot-url}に置き換えてください。（@<list>{ai-chat-source-code}）

//footnote[ai-chat-bot-url][このコードはGitHubで公開されている本書のリポジトリからもダウンロードできます。 @<href>{https://github.com/mochikoAsTech/startLINEBot/blob/master/articles/aichatbot.py}]

//listnum[ai-chat-source-code][AIチャットボットが自動で応答するコード][python]{
import json
import logging
import openai
import os
import sys

from linebot import LineBotApi, WebhookHandler
from linebot.exceptions import InvalidSignatureError, LineBotApiError
from linebot.models import MessageEvent, TextMessage, TextSendMessage

# INFOレベル以上のログメッセージを拾うように設定する
logger = logging.getLogger()
logger.setLevel(logging.INFO)

# 環境変数からMessaging APIのチャネルアクセストークンとチャネルシークレットを取得する
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')

# 環境変数からOpenAI APIのシークレットキーを取得する
openai.api_key = os.getenv('SECRET_KEY')

# それぞれ環境変数に登録されていないとエラー
if CHANNEL_ACCESS_TOKEN is None:
    logger.error(
        'LINE_CHANNEL_ACCESS_TOKEN is not defined as environmental variables.')
    sys.exit(1)
if CHANNEL_SECRET is None:
    logger.error(
        'LINE_CHANNEL_SECRET is not defined as environmental variables.')
    sys.exit(1)
if openai.api_key is None:
    logger.error(
        'Open API key is not defined as environmental variables.')
    sys.exit(1)

line_bot_api = LineBotApi(CHANNEL_ACCESS_TOKEN)
webhook_handler = WebhookHandler(CHANNEL_SECRET)

# 質問に回答をする処理


@webhook_handler.add(MessageEvent, message=TextMessage)
def handle_message(event):

    # ChatGPTに質問を投げて回答を取得する
    question = event.message.text
    answer_response = openai.ChatCompletion.create(
        model='gpt-3.5-turbo',
        messages=[
            {'role': 'user', 'content': question},
        ],
        stop=['。']
    )
    answer = answer_response["choices"][0]["message"]["content"]
    # 受け取った回答のJSONを目視確認できるようにINFOでログに吐く
    logger.info(answer)

    # 応答トークンを使って回答を応答メッセージで送る
    line_bot_api.reply_message(
        event.reply_token, TextSendMessage(text=answer))

# LINE Messaging APIからのWebhookを処理する


def lambda_handler(event, context):

    # リクエストヘッダーにx-line-signatureがあることを確認
    if 'x-line-signature' in event['headers']:
        signature = event['headers']['x-line-signature']

    body = event['body']
    # 受け取ったWebhookのJSONを目視確認できるようにINFOでログに吐く
    logger.info(body)

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
//}

このコードの中で、次の部分がOpenAI APIをたたいて質問の回答を取得するコードです。OpenAI APIに質問を投げると、回答の生成に非常に時間がかかるため、@<ttb>{stop=['。']}を指定することで、「最初に句点（。）が出てきたらそこで生成を終了する」というリクエストにして回答生成を早めに切り上げるようにしています。（@<list>{qanda-code}）

//listnum[qanda-code][OpenAI APIをたたいて質問の回答を取得する部分のコード][python]{
    # ChatGPTに質問を投げて回答を取得する
    question = event.message.text
    answer_response = openai.ChatCompletion.create(
        model='gpt-3.5-turbo',
        messages=[
            {'role': 'user', 'content': question},
        ],
        stop=['。']
    )
    answer = answer_response["choices"][0]["message"]["content"]
//}

コードを直したら、［Deploy］を押してデプロイ（変更後のコードを反映）します。（@<img>{aichat-bot-deploy-1}）

//image[aichat-bot-deploy-1][［Deploy］を押して変更後のコードを反映する][scale=0.8]{
//}

［関数 Bot-Server-on-Lambda が正常に更新されました。］と表示されたらデプロイ完了です。（@<img>{aichat-bot-deploy-2}）

//image[aichat-bot-deploy-2][デプロイ完了][scale=0.8]{
//}

=== Lambda関数のタイムアウトまでの時間を延ばす

いまデプロイしたAIチャットボットのコード（@<list>{ai-chat-source-code}）で、45行目以降のOpenAI APIに質問を投げて回答を取得する部分は、回答が返ってくるまでに数秒以上かかる場合があります。@<fn>{response-time}

//footnote[response-time][@<hd>{article02|openai-api-curl}でcurlコマンドをたたいたとき、レスポンスが返ってくるまでにちょっと待ち時間があったことを思い出してください。]

実はLambda関数には、コードを実行してからn秒立ったらタイムアウトする、つまり処理を打ち切る、という最長実行時間があります。［設定］タブの［一般設定］を開くと、［タイムアウト］が@<ttb>{0分3秒}になっていますね。タイムアウトのデフォルト値はこの通り3秒なので、Webhookが届いてコードを実行しはじめてから3秒以内にすべての処理が終わらないと、そこで処理が打ち切られてしまうのです。［編集］をクリックしてください。（@<img>{timeout}）

//image[timeout][［編集］をクリックしてタイムアウトの秒数を変更しよう][scale=0.8]{
//}

このままの設定だと、OpenAI APIに質問を投げてから回答が戻ってくるまでに3秒以上かかった場合、タイムアウトして処理が打ち切られてしまうため、この［タイムアウト］の秒数を@<ttb>{3秒}から@<ttb>{30秒}@<fn>{seconds}に変更して［保存］します。（@<img>{timeout-2}）

//image[timeout-2][［タイムアウト］を30秒に変更して［保存］しよう][scale=0.8]{
//}

//footnote[seconds][ちなみにAWS Lambdaの手前にいるAPI Gatewayにもタイムアウトがあり、そちらは最大29秒で変更もできなません。そのため、本書の構成だと仮にLambda関数のタイムアウトをもっと長い60秒や90秒にしたとしても、先にAPI Gatewayがタイムアウトしてしまうのであまり意味がありません。]

Lambda関数の［タイムアウト］が@<ttb>{30秒}に変更されました。（@<img>{timeout-3}）

//image[timeout-3][［タイムアウト］が30秒になった][scale=0.8]{
//}

それでは最後に、環境変数の設定を追加しましょう。

=== 環境変数にOpenAIのシークレットキーを追加する

いまデプロイしたAIチャットボットのコードを実際に動かすには、OpenAI APIのシークレットキーが必要です。チャネルアクセストークンやチャネルシークレットと同様に、シークレットキーもソースコードには直接書かず、環境変数として設定しておいて、コードからは@<ttb>{openai.api_key = os.getenv('SECRET_KEY')}というように環境変数を参照する形にしています。

Lambda関数の［設定］タブから［環境変数］を開いて、［編集］をクリックします。（@<img>{add-secret-key-to-env-1}）

//image[add-secret-key-to-env-1][［環境変数］の［編集］をクリックする][scale=0.8]{
//}

［環境変数の追加］をクリックして、［キー］と［値］を次のように設定します。シークレットキーは、@<hd>{article02|issue-secret-key}でコピーしてメモ帳に保存してあるはずです。（@<table>{set-openai-env}）

//table[set-openai-env][環境変数の編集]{
キー	値
--------------------
SECRET_KEY	シークレットキー
//}

環境変数を編集したら［保存］をクリックします。（@<img>{add-secret-key-to-env-2}）

//image[add-secret-key-to-env-2][環境変数を編集したら［保存］をクリックする][scale=0.8]{
//}

［関数 Bot-Server-on-Lambda が正常に更新されました。］と表示されたら、環境変数にOpenAIのシークレットキーを追加する設定は完了です。（@<img>{add-secret-key-to-env-3}）

//image[add-secret-key-to-env-3][環境変数の設定完了][scale=0.8]{
//}

これでボットサーバーのボットを、オウム返しするボットからAIチャットボットに切り替える作業が終わりました。

=== LINE公式アカウントに話しかけてAIチャットボットの回答を確認しよう

それではLINE公式アカウントに質問をしてみて、AIチャットボットが回答してくれることを確認してみましょう。（@<img>{aichat-reply}）

//image[aichat-reply][メッセージを送ったらAIチャットボットが返事をしてくれた][scale=0.8]{
//}

さっきはオウム返しをするだけだったのに、AIチャットボットが回答をしてくれるようになりました！おめでとうございます！これでAIチャットボットの完成です。

===[column] 【コラム】Webhookへのレスポンスが先？応答メッセージが先？

ボットサーバーでWebhookを受け取った際、Webhookのその内容に応じた処理や応答メッセージの送信などをしてからステータスコード200を返す、という順番はお勧めしません。

なぜなら間に挟まる処理や応答メッセージ送信などに時間がかかった場合、レスポンスを返す前にLINEプラットフォームから送られたWebhookのリクエストがタイムアウトしてしまう可能性があるためです。

なんとなく先に色々片付けてからレスポンスを返したい気持ちは分かりますが、郵便局員が郵便物を持って来てくれたとき、わざわざ玄関前で待たせて封筒を開けて中身を読んでからようやく受領の判子を押してあげる、という順番だとおかしいよね、と考えると納得しやすいのではないでしょうか。先ずは受領の判子を押して郵便局員を帰らせてあげて、手紙を読んだり、返事を書いたりはそのあとでやりましょう。@<fn>{sorry-but}

またメッセージに対する応答メッセージを送る場合、応答トークンはWebhookを受信後、速やか（具体的には1分以内）に使う必要があります。@<fn>{reply_token_rule}Webhook受信後、すぐに返信を送れる場合は応答メッセージで構いませんが、色々な処理を行ってかなり時間が経ってから返信したい場合は、応答トークンが既に無効になっている可能性があります。その場合は、対象となる友だちのユーザーIDを指定したプッシュメッセージで返信を送ることが可能です。

===[/column]

//footnote[sorry-but][この「Webhookを受け取ったら、先にレスポンスを返してその後に応答メッセージなどの処理をすべき」という説明を読んで、勘の良い読者の方はもうお気づきかもしれませんが、実は本書ではオウム返しボットのコードもAIチャットボットのコードも、郵便局員を待たせまくって、なんなら返信を書いてポストに投函してからようやく受領の判子を押しています。非同期処理まで含めると手順や説明が非常に複雑になってしまうため、本来はあまり推奨されない方法だと理解した上で、今回は動くものを簡単に作れることを優先して敢えてそうしています。]
//footnote[reply_token_rule][応答トークン | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#send-reply-message-reply-token}]
