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

通常、私たちはブラウザでURLを入力したり、リンクをクリックしたりすることで「このウェブページを見せてくれ！」とサーバーにリクエストを投げ、リクエストを受けたウェブサーバーが「はい、どうぞ」とウェブページをレスポンスで返してくれます。（@<img>{request-and-response}）

//image[request-and-response][ブラウザでウェブページを見るときのリクエストとレスポンス][scale=1]{
//}

REST APIは、このウェブページと同じように、ウェブサーバー上で提供されます。私たちがcurlコマンド@<fn>{curl}や、Postman@<fn>{postman}や、プログラムを通じてREST APIに対して「天気情報をくれ！」とか「メッセージを送信してくれ！」というリクエストを投げると、ウェブサーバー上でうごくREST APIが「君が求めていた天気情報はこれだよ！」とか「メッセージの送信に成功したよ！」というようにレスポンスを返してくれるのです。（@<img>{api-request-and-response}）

//footnote[curl][curk（カール）はHTTPやHTTPS、SCP、LDAPなど、さまざまなプロトコルでデータ転送ができるコマンドです。今までにcurlを使ったことのない人とっては、この説明を読んでもいまいちピンとこないと思うので、「ターミナル」という種類のソフトで、ブラウザのようなことができるコマンドだと思っておいてください。ちなみにターミナルは、エンジニア以外の方には、いわゆる「黒い画面」と言った方がお馴染みかもしれません。]
//footnote[postman][Postmanは、GUIの画面でREST APIを叩ける便利なツール。 @<href>{https://www.postman.com/}]

//image[api-request-and-response][REST APIをたたくときのリクエストとレスポンス][scale=1]{
//}

前述のとおり、APIは広義には「情報をやりとりする窓口」であり、様々なものを内包していますが、本書においてはただ「API」と呼んだら、それはREST APIのことを指していると思ってください。

=== Messaging APIとは

ではあらためて、Messaging APIについて説明していきましょう。Messaging APIは、LINE公式アカウントからのメッセージ送信や、返信などの操作ができるAPI@<fn>{use-messaging-api}です。LINE株式会社が無料で提供しており、LINE Developersコンソールと呼ばれる開発者向けの管理画面でアカウント登録をすれば誰でも利用できます。@<fn>{price}

//footnote[use-messaging-api][Messaging APIは、あくまでLINE公式アカウントの操作をするためのAPIなので、個人のLINEアカウントで受信したメッセージをSlackに転送する、というようなことはできません。]
//footnote[price][Messaging APIの各APIをたたくこと自体に費用はかかりません。@<chapref>{article01}の@<hd>{article01|oaprice}で紹介したとおり、送れるメッセージの通数を増やすために有料のプランを契約したときに初めてお金がかかります。]

Messaging APIを使用することで、開発者はユーザーがLINE公式アカウントに送ったメッセージを受信したり、LINE公式アカウントから友だちに対して返信を送ったり、友だちとなったユーザーのプロフィール情報を取得したりすることができます。

実際にMessaging APIを使用するためには、LINE公式アカウントと紐づく形でMessaging APIチャネルというものを作って、APIの利用に必要な「チャネルアクセストークン」というものを取得する必要があります。

LINE公式アカウントとMessaging APIチャネルの関係は、初見だとちょっと分かりにくいので、実際にMessaging APIチャネルを作る前にそこを少し説明していきます。

== Messaging APIチャネルを作ろう

LINE公式アカウントとMessaging APIチャネルは、表と裏のような存在です。LINE公式アカウントを単体で作って、LINE Official Account Managerや管理アプリを使って中の人が頑張ることもできますが、裏側にMessaging APIチャネルを紐づけて、ボットが自動で応答するように設定することも可能です。（@<img>{messaging-api-channel}）

//image[messaging-api-channel][LINE公式アカウントとMessaging APIチャネルは表と裏][scale=1]{
//}

あなたはさっき、LINEでLINE公式アカウントを作ったので、いまは表のLINE公式アカウントだけが在って、裏に控えるMessaging APIチャネルは存在していない状態です。

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

//footnote[business-id][LINEビジネスIDはLINE Official Account Manager、LINE公式アカウントの管理アプリ、LINE Developersコンソールなどで採用されている共通認証システム。1つのアカウントですべてに共通してログインできる。実はさっき管理アプリにログインしたときも、この共通認証システムを使っていたのです。]

//image[line-for-business-login-2][［LINEアカウントでログイン］を選ぶ][scale=0.8]{
//}

@<hd>{article01|create-account}で登録したメールアドレスと、LINEのパスワード@<fn>{password}を入力して、［ログイン］しましょう。入力が面倒な場合は、［QRコードログイン］からQRコードを表示して、それをスマートフォンのLINEのQRコードスキャンで読み込む形でもログイン可能です。（@<img>{line-for-business-login-3}）

//footnote[password][「LINEのパスワードなんて設定したっけ？何も覚えていません」という人はLINEを開いて、下に並んでいる［ホーム］から右上の歯車アイコンをタップして［設定］を開き、［アカウント］の［パスワード］からすぐに新しいパスワードを設定できます。 @<href>{https://guide.line.me/ja/account-and-settings/account-and-profile/set-password.html}]

//image[line-for-business-login-3][メールアドレスとパスワードを入力して［ログイン］する][scale=0.8]{
//}

二要素認証のため、4桁の認証番号が表示されます。（@<img>{line-for-business-login-4}）

//image[line-for-business-login-4][4桁の認証番号が表示される][scale=0.8]{
//}

スマートフォンのLINEを開くと、認証番号入力の画面が表示されますので、4桁の認証番号を入力して［本人確認］をタップします。［ログインしました］と表示されたら、［確認］をタップします。@<img>{line-for-business-login-5}）

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

//footnote[mochiko][私は名前の欄に個人事業主としての屋号（mochikoAsTech）を記入していますが、個人開発者として登録するのであれば普通に氏名の入力で構わないと思います。]
//footnote[mail-address][ここで登録するメールアドレスは、LINEに登録してあるメールアドレスとは別のアドレスでも構いません。開発者に対するお知らせを送ってほしいメールアドレスを記入しましょう。ただしLINE Developersコンソールへのログインに使用するメールアドレスは、LINEに登録してあるメールアドレスであって、ここで記入したメールアドレスではないので、その点は注意してください。]

//image[create-messaging-api-channel-5][［名前］と［メールアドレス］を入力して［同意する］を押す][scale=0.8]{
//}
     
入力した開発者情報の確認画面が表示されます。表示されている内容で問題なければ、［OK］を押します。（@<img>{create-messaging-api-channel-6}）

//image[create-messaging-api-channel-6][表示されている内容で問題なければ［OK］を押す][scale=0.8]{
//}

開発者情報を登録すると、今度はプロバイダーの選択画面が表示されます。プロバイダーとは、サービスを提供し、ユーザーの情報を取得する企業や開発者個人のことを指し、これから作成するMessaging APIチャネルは、このプロバイダーというものの下に属します。プロバイダーの下には、複数のチャネルが所属できます。

運営元が個人だと「チャネルもプロバイダーも全部俺だ！」みたいになって違いが分かりにくいですが、たとえば飲料メーカーのA社が「炭酸飲料B」と「コーヒー飲料C」という2つのブランドを展開していた場合、プロバイダー名は「A社」になり、その配下にあるMessaging APIチャネル名は「炭酸飲料B」や「コーヒー飲料C」になります。@<fn>{provider}（@<img>{providers-and-channels}）

//image[providers-and-channels][チャネルはプロバイダーの配下に属する][scale=0.6]{
//}

//footnote[provider][複数のチャネルがあって、1つのプロバイダー配下に収めたときと、それぞれプロバイダーを分けたときで何が変わるかというと、ユーザーIDの扱いが変わります。ユーザーを一意に識別するためのユーザーIDは、同じユーザーであってもプロバイダーごとに異なる値が発行されます。つまりmochikoさんというひとりのユーザーがいたとき、「A社」というプロバイダーの配下にあるチャネルから見たmochikoさんのユーザーIDと、また別の「B社」というプロバイダーの配下にあるチャネルからみたmochikoさんのユーザーIDは別々の値になるのです。そのため、本書では詳しく触れませんがLINEログインチャネルとMessaging APIチャネルでユーザー情報を連携したい場合は、その2つのチャネルが同一のプロバイダー配下にいなければならない、などの制約があります。一度チャネルをプロバイダーと紐づけてしまうと、後から「あっちのプロバイダー配下に移動させたい！」と思っても、絶対に移動できないので注意してください。]

あなたが個人の開発者なのであれば、プロバイダー名は個人名でも構いません。誰かに「このLINE公式アカウントの運営元はどこなんですか？」と聞かれたときに、あなたが答えるであろう名称をプロバイダー名にしましょう。

まだプロバイダーというものを1つも持っていないので、今回は［プロバイダーを作成］します。プロバイダー名を入力して、「LINE公式アカウントAPI利用規約」を確認し、［同意する］を押します。（@<img>{create-messaging-api-channel-7}）

//image[create-messaging-api-channel-7][プロバイダー名を入力して［同意する］を押す][scale=0.8]{
//}
     
もしあなたがサービス提供者として、プライバシーポリシーや利用規約を既に持っていたら、プロバイダーのプライバシーポリシーと利用規約としてここでURLを登録できます。個人開発者であればどちらも持っていないと思いますので、その場合は何も入力せずに［OK］を押して進んで構いません。（@<img>{create-messaging-api-channel-8}）

//image[create-messaging-api-channel-8][入力せずに［OK］を押す][scale=0.8]{
//}

このLINE公式アカウントを、このプロバイダーと紐づけますがいいですか、という最終確認の画面が表示されます。記載のとおり、一度チャネルをプロバイダーと紐づけてしまうと、後から「あっちのプロバイダー配下に移動させたい！」と思っても、絶対に移動できないので、プロバイダー名はよく確認してください。問題なければ［OK］を押します。（@<img>{create-messaging-api-channel-9}）

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

ついでに［チャネル基本設定］タブのチャネルシークレットもコピーして、一緒にメモしておきましょう。（@<img>{console-6}）

//image[console-6][チャネルアクセストークンもコピーする][scale=0.8]{
//}

チャネルアクセストークンとチャネルシークレットが手に入ったので、早速Messaging APIでメッセージを送ってみましょう。

==={curl} Messaging APIでブロードキャストメッセージを送信する

実は、ただメッセージを送るだけならウェブサーバーは必要ありません。あなたのパソコンでcurlコマンドをたたくことで、Messaging APIを使ってメッセージを送信できます。あなたが使っているパソコンがWindowsならWSL（@<img>{wsl}）@<fn>{wsl}、Macならターミナル（@<img>{mac}）を起動してください。

//image[wsl][WindowsならWSLを起動する][scale=0.8]{
//}

//footnote[wsl][WSLとはWindows Subsystem for Linuxの略で、Windows上で動くLinux環境のことです。]

Macを使っている方は、最初から「ターミナル」（@<img>{mac}）というソフトがインストールされていますのでそちらを利用しましょう。

//image[mac][Macならターミナルを起動する][scale=0.8]{
//}

WSLやターミナルがどこにあるのか分からないときは、Windowsなら画面下部の検索ボックスで「WSL」と検索（@<img>{search-wsl}）、Macなら画面右上にある虫眼鏡のマークからSpotlightで「ターミナル」と検索（@<img>{search-mac}）すれば起動できます。

//image[search-mac][Windowsなら検索ボックスで「WSL」と検索][scale=0.8]{
//}

//image[search-wsl][MacならSpotlightで「ターミナル」と検索][scale=0.8]{
//}

curlコマンド（@<list>{curl-send-message}）の3行目にある「チャネルアクセストークン」の部分を、Messaging APIチャネルのチャネルアクセストークンに置き換えてください。チャネルアクセストークンは、先ほど@<hd>{article02|issue-token}でコピーしましたね。

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

レスポンスが画面に出力され、curlコマンドを使ってAPIをたたいた結果、ステータスコード200と空のJSONオブジェクトが返ってきたことが分かります。（@<img>{curl-3}）

//image[curl-3][ステータスコード200が返ってきた][scale=0.8]{
//}

すると、Messaging APIで送ったメッセージがLINEに届きました！（@<img>{broadcast-message}）

//image[broadcast-message][Messaging APIで送ったメッセージが届いた][scale=0.4]{
//}

やったぁ！Messaging APIが叩けましたね！おめでとうございます。

いまあなたがたたいたのは、LINE公式アカウントと友だちになっている人全員にメッセージを送るための「ブロードキャストメッセージを送る」いうAPIです。もしcurlコマンドを実行した後にステータスコード200以外が返ってきて、LINEにメッセージが届かなかった場合は、APIリファレンス@<fn>{broadcast-message}でこのAPIのエラーレスポンスを確認してみてください。

//footnote[broadcast-message][ブロードキャストメッセージを送る | Messaging APIリファレンス | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#send-broadcast-message}]

メッセージが届いたら、textの部分を好きなテキストにしたり、公開されている「送信可能なスタンプリスト@<fn>{stamp}」を見ながらcurlコマンドのpackageIdやstickerIdを好きなものに変えてみたりして、メッセージを何度か送り直してみましょう。（@<img>{broadcast-message-2}）

//image[broadcast-message-2][テキストやスタンプを変えてメッセージを何度か送ってみよう][scale=0.4]{
//}

//footnote[stamp][@<href>{https://developers.line.biz/ja/docs/messaging-api/sticker-list/}]

APIをたたくと、手元のスマートフォンでLINEにメッセージが届く。こうして自分がやったことが、ちゃんと動いて目に見えるのはとってもうれしいですよね。

===[column] 【コラム】仕事でLINE Botを開発するときにも「個人のLINEアカウント」が必要か？

Messaging APIを使って開発をするとき、様々な設定をするための管理画面が「LINE Developersコンソール」です。このLINE Developersコンソールにログインするには、LINEアカウントまたはビジネスアカウントのどちらかが必要です。

すでにスマートフォンでLINEを使っていれば、そのLINEアカウントでそのままログインできます。本書では、@<chapref>{article01}でLINE公式アカウントを作ったときのLINEアカウントで、LINE Developersコンソールにログインしています。

個人開発であればこれで問題ありませんが、仕事の場合は「私物のスマホに入れている個人のLINEアカウントを業務で使うのはちょっと…」というケースももちろんあると思います。その場合は業務用のメールアドレスでビジネスアカウントを作りましょう。ただしビジネスアカウントでログインした場合は、Messaging APIチャネルが作れないなど、できることに一部制限@<fn>{limited}があります。

その場合は、プロジェクトの中で誰かひとりが会社の検証端末にLINEを入れ、そのLINEアカウントでLINE Developersコンソールにログインして、Messaging APIチャネルを作ればいいのです。後はそのプロバイダーやチャネルに、他のメンバーのビジネスアカウントをAdmin権限で追加してやれば、開発を進める上で問題はないでしょう。

===[/column]

//footnote[limited][LINE Developersコンソールへのログイン | LINE Developers @<href>{https://developers.line.biz/ja/docs/line-developers-console/login-account/}]

== LINE公式アカウントから友だちに返信するには

さて、ここまでは「LINE公式アカウントからメッセージを送る」という、LINE公式アカウント起点の話をしてきました。LINE公式アカウント起点というのは、たとえば今月の定休日を知らせるメッセージを送るとか、新商品が出たときにメッセージを送るとかいうように、LINE公式アカウント側が「送りたい！」と思った任意のタイミングでメッセージを送る、ということです。

でも片方が話したいときだけ一方的に話すのでは、それは対話とは言えません。ユーザーが友だち追加してくれたときや、ユーザーが何か質問してきたとき、ユーザーがリッチメニュー@<fn>{rich}をタップしたときなど、ユーザー起点のコミュニケーションにきちんと反応できるようになってこそのチャットボットです。

//footnote[rich][リッチメニューについては、@<hd>{article03|richmenus}で後述します。]

ではユーザー起点のメッセージにLINE公式アカウントが反応するには、どうしたらいいのでしょう？ユーザーからのメッセージに応対する方法は、大きく分けて4つあります。

==={reply} 方法1. 固定の自動応答を設定しておいて個別の応対は一切しない

1つめは、LINE Official Account Managerで次のような固定の「応答メッセージ」を設定しておいて、個別の応対は一切しないという方法です。@<hd>{article01|try-message}で「新刊買います！」をメッセージを送ったときに受け取ったメッセージなので見覚えがありますね。（@<img>{auto-res}）

//image[auto-res][自動の応答メッセージ][scale=0.6]{
//}

この自動の応答メッセージはデフォルトで設定されているので、あなたも友だち追加したLINE公式アカウントでよく似たメッセージを見たことがあるかもしれません。

これだと個別対応のコストが一切要らなくなるものの、ユーザー起点のコミュニケーションはできなくなるので、LINE公式アカウントとのトークは一方的な宣伝をするだけの場所になります。ただ、少なくとも話しかけたのに何も応答せず無言でいられるよりは、まだ気分がいいかもしれません。

=== 方法2. 人間が手打ちのチャットで返信する

2つめは「中の人」が頑張って手打ちのチャットで返信する、という方法です。LINE Official Account Managerや管理アプリにはチャットの機能があるので、「中の人」がその機能でユーザーからのメッセージを確認して、手打ちのチャットで頑張って応対します。

たとえば個人で経営する小さなヘアサロンで、予約を電話じゃなくLINEのトークで受け付けたい、というような場合は、このチャットで必要十分なケースもあるでしょう。

=== 方法3. 内容に応じた自動応答メッセージで応対する
     
3つめは内容に応じた自動応答メッセージを用意しておいて自動で返信する、という方法です。

LINE Official Account Managerや管理アプリには、応答メッセージとAI応答メッセージ@<fn>{reply_and_ai}というものがあります。応答メッセージはキーワードとメッセージを事前に設定しておくことで、ユーザーがそのキーワードと完全一致するメッセージを送ってきたら、自動でメッセージを返信する機能です。完全に一致する必要があるので、たとえば「メニュー」というキーワードの場合、ユーザーが「メニュー」とだけ送ってくれば応答できますが、「メニューは？」と送ってきた場合は応答できません。

//footnote[reply_and_ai][自動応答が可能に！「応答メッセージ」と「AI応答メッセージ」とは｜LINE for Business @<href>{https://www.linebiz.com/jp/column/technique/20191128/}]

一方、AI応答メッセージはもう少し融通が利いて、ユーザーから送られたメッセージの内容をAIが判別して、適切なメッセージで自動で返信してくれます。たとえば飲食店なら、営業時間、住所、Wi-Fi、コンセント、駐車場、喫煙可否など、質問が想定されることについてそれぞれ事前に返信メッセージを設定しておくことで、単語が完全に一致しなくてもよしなに回答してくれます。たとえば「Wi-Fi」に対して「申し訳ありませんがWi-Fiはご利用いただけません」という回答をオンにしておくと、「Wi-Fiってありますか？」のようなメッセージだけに限らず、「ネットって使えたりする？」「無線ってありますか？」「無料のわいふぁいって使える？」といったメッセージでもきちんとその回答が返ってきます。

応答メッセージとAI応答メッセージは、どちらか片方だけ使うこともできますし、キーワードに完全一致したら応答メッセージを返して、そうでない場合はAI応答メッセージを返す、というように両方使うこともできます。

さらに方法2と方法3を併用することも可能です。LINE Official Account Managerや管理アプリで営業時間を設定しておくことで、営業時間内は中の人が手打ちのチャットで応答して、営業時間外は自動応答のメッセージに任せる、というような運用ができます。

=== 方法4. Messaging APIで返信する

4つめはMessaging APIで返信する、という方法です。Messaging APIでは、この「ユーザー起点のコミュニケーション」に気づく方法として、Webhookというものが用意されており、このWebhookをボットサーバーで受け止めることでボットから返信ができます。ではWebhookとはいったいどんなものなのでしょう？

=== Webhookとは

ユーザーが、LINE公式アカウントを友だち追加したり、ブロックしたり、LINE公式アカウントにメッセージを送ったりというように、何かしらの「イベント」を起こすと、LINEプラットフォームからボットサーバーに対して、Webhookが送られます。LINEプラットフォームから送られてくるWebhookを受け止めるためには、LINE公式アカウントを運営するあなたが自分でこのボットサーバーを用意する必要があります。（@<img>{webhook}）

//image[webhook][ユーザーがメッセージを送るとボットサーバーにWebhookが飛んでくる][scale=0.8]{
//}

通常、私たちはブラウザでショッピングサイトのマイページを開いて、住所を入力して送信ボタンを押すことで、ウェブサーバーに「住所情報をこれに変更にしてくれ！」とリクエストを投げ、リクエストを受けたウェブサーバーが諸々の処理をしてから「はい。住所変更終わりましたよ」と変更完了ページをレスポンスで返してくれたりします。このときは、ウェブサーバー側が「サーバー」で、自分やブラウザ側が「クライアント」です。

しかしWebhookにおいてはこれが逆転します。LINEプラットフォームから「ユーザーがこんなメッセージを送ってきたよ！Webhookを受け取って！」とリクエストが飛んでくるので、あなたが用意したボットサーバーでそれを受け取って、「ありがとう！Webhookちゃんと受け取ったよ！ステータスコード200！」というレスポンスを返さなければいけません。Webhookを投げてくるLINEプラットフォームが「クライアント」で、あなたの用意するボットサーバーが「サーバー」なのです。

私たちはクライアントになる経験はよくしていますが、サーバーの立場になる経験はあまりないのでなんだか不思議な感じがしますが、ことWebhookにおいては、あなたは「ボットサーバーを用意する側」であり、「Webhookを受け取ってレスポンスを返す側」なのです。

あんまりピンとこないかもしれませんが、この説明だけでWebhookを完璧に理解できなくても大丈夫です。手を動かしてボットサーバーを用意し、実際にWebhookを受け取って返信を返してみましょう。

===[column] 【コラム】LINE公式アカウントの「既読」はいつ付くのか？

普通の友だちとのLINEのメッセージは、相手がトークルームを開いてメッセージを見ることで「既読」がつきます。ではLINE公式アカウントの場合は、「既読」はいつ付くのでしょう？

LINE Official Account Managerや管理アプリの応答設定に「チャット」と「Webhook」という設定項目があります。この「チャット」をオンにしていると、中の人がチャットの画面でメッセージを確認するまでは、LINE公式アカウント側でメッセージを読んだことを示す「既読」マークがつきません。逆にこの「チャット」をオフにしていると、メッセージが送られた瞬間に自動的に「既読」がつきます。

Messaging APIを使ってLINE公式アカウントから自動応答しているのに、なぜか「既読」マークが付かない！というときは、うっかり応答設定で「チャット」をオンにしないか確認してみてください。応答設定で「Webhookだけをオンにしている」だと自動で既読が付きますが、「チャットだけをオンにしている」もしくは「チャットとWebhookの両方をオンにしている」状態だと、チャットの画面でメッセージを確認するまで既読が付きません。

チャットもWebhookも両方をオンにしたいけど、チャット画面で確認するんじゃなくて自動で既読を付けたい、という場合は「既読API@<fn>{mark-as-read}」というAPIを使うことで既読が付けられますが、残念ながら既読APIは法人ユーザー限定のオプション機能です。

===[/column]

//footnote[mark-as-read][既読API | LINE Developers @<href>{https://developers.line.biz/ja/docs/partner-docs/mark-as-read/}]

== オウム返しするチャットボットを作ってみよう

メッセージをWebhookで受け取って返信するまでの一連の流れを理解するため、先ずは一番簡単な「オウム返しするチャットボット」を作ってみましょう。

==={prepare-messaging-api-sdk} Messaging APIのSDKを準備する

Messaging APIでは、開発をサポートするSDK@<fn>{sdk}がJava、PHP、Go、Perl、Ruby、Python、Node.jsで用意@<fn>{messaging-api-sdk}されています。今回はPythonのSDKを使ってコードを書いていきます。

//footnote[sdk][SDKはSoftware Development Kitの略。名前のとおり開発に必要なライブラリが詰まった工作キットのようなものです。たとえば料理でも、材料を揃えて野菜の皮を剥くところからやるととても大変ですが、下ごしらえの済んだ材料とレシピがひとまとめになっているミールキットを使えば、誰でも短時間で失敗もなく美味しい食事が作れます。それと同じで、開発においてもSDKが用意されていたら、そのSDKを使うことで色々とラクができます。]
//footnote[messaging-api-sdk][LINE Messaging API SDK | LINE Developers @<href>{https://developers.line.biz/ja/docs/messaging-api/line-bot-sdk/}]

 * LINE Messaging API SDK for Python
 ** @<href>{https://github.com/line/line-bot-sdk-python}

==== Windowsの場合

@<hd>{article02|curl}で使用したWSLを再び起動して、以下のコマンドを順番にたたいていきます。@<b>{$}はプロンプトを表していますので入力しないでください。

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

続いて、SDKをパソコンの中に取ってくるためにpipコマンドが使いたいので、aptコマンドでpipコマンドを連れてきます。@<b>{sudo apt update}をたたくとパスワードを聞かれるので、パソコンを起動したときに入力するのと同じパスワードを入力してEnterを押してください。@<b>{sudo apt install python3-pip}をたたくと、メッセージがだだーっと流れた後に@<b>{Do you want to continue? [Y/n]}と聞かれるので、Yを入力してEnterを押してください。

//cmd{
$ sudo apt update
$ sudo apt install python3-pip
//}

いよいよpipコマンドでSDKをパソコンの中に取ってきます。lsコマンドでpythonディレクトリの中身を確認して、なんだかたくさん入っていればOKです。（@<img>{get-sdk-2}）

//cmd{
$ pip install line-bot-sdk -t . --no-user
$ ls
//}

//image[get-sdk-2][取ってきたSDKがpythonディレクトリの中にみっしり入っている][scale=1]{
//}

取ってきたSDKをぎゅっとZIPに固めたいので、cdコマンドで1つの上のディレクトリに移動しましょう。そしてaptコマンドでzipコマンドを連れてきます。@<b>{sudo apt install zip}をたたくと、メッセージがだだーっと流れた後に@<b>{Do you want to continue? [Y/n]}と聞かれるので、Yを入力してEnterを押してください。

//cmd{
$ cd ..
$ sudo apt install zip
//}

それではzipコマンドでpythonディレクトリをぎゅっとZIPに固めましょう。lsコマンドでpython.zipとpythonディレクトリが確認できればOKです。（@<img>{get-sdk-3}）

//cmd{
$ zip -r python.zip python
$ ls
//}

//image[get-sdk-3][zipコマンドでpythonディレクトリをZIPに固める][scale=1]{
//}

最後に@<b>{explorer.exe .}をたたくと、WSLで見ていたディレクトリがエクスプローラで表示されます。（@<img>{get-sdk-4}、@<img>{get-sdk-5}）

//cmd{
$ explorer.exe .
//}

//image[get-sdk-4][「explorer.exe .」をたたく][scale=1]{
//}

//image[get-sdk-5][するとエクスプローラでpython.zipのあるフォルダが表示される][scale=0.8]{
//}

作成したpython.zipはこの後すぐに使うので、デスクトップにコピーしておきましょう。（@<img>{copy-to-desktop}）

//image[copy-to-desktop][python.zipはデスクトップにコピーしておく][scale=0.8]{
//}

これでMessaging APIのSDKが準備できました。

==== Macの場合

Macの場合は、デフォルトでpipコマンドやzipコマンドが入っているので、Windowsの手順から@<b>{sudo apt install ○○}というコマンドを除いて同様に実行してください。

=== AWS LambdaとAPI Gatewayでボットサーバーを作る

今回はWebhookを受け取って、ステータスコード200を返して、応答メッセージを送るボットサーバーとして、AWSのサーバーレスサービス、AWS LambdaとAPI Gatewayを使用します。

AWSを初めて使用する場合、AWSアカウントを作成してから1年間は利用料が無料となります。ただし無料利用枠の範囲は決まっており、何をどれだけ使っても無料という訳ではありません。どのサービスをどれくらい無料で使えるのか？は「AWS無料利用枠」のページ（@<href>{https://aws.amazon.com/jp/free/}）」に記載されていますので、そちらを参照してください。AWSアカウントを持っていない場合は、同じ「AWS無料利用枠」のページにある［無料アカウントの作成］から作成してください。@<fn>{create-aws-account}（@<img>{awsFree}）

//image[awsFree][AWS無料利用枠][scale=0.8]{
//}

//footnote[create-aws-account][なおAWSアカウントの作成の詳しい手順は「DNSをはじめよう」という書籍で、またAWSとは何かについての説明や、無料利用枠の範囲、利用金額が一定額を超えたらアラートが飛ぶようにする設定などは「AWSをはじめよう」という書籍で詳しく紹介しています。もしAWSアカウントの作成や設定に不安がある場合は、そちらを参考にしてください。 @<href>{https://mochikoastech.booth.pm/}]

それでは早速、AWSのマネジメントコンソール（@<href>{https://console.aws.amazon.com/}）を開いて、上部の検索窓で@<b>{lambda}と検索し、Lambdaを開きます。（@<img>{search-lambda}）

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

［アップロード］をクリックしたら、@<hd>{article02|prepare-messaging-api-sdk}で作成してデスクトップに置いたZIPファイルを選択し、アップロードしてください。（@<img>{select-python-zip}）

//image[select-python-zip][デスクトップにあるpython.zipを選択してアップロード][scale=0.8]{
//}

必要事項を入力したら［作成］をクリックします。（@<img>{create-layer-2}）

//image[create-layer-2][必要事項を入力したら［作成］をクリックする][scale=0.8]{
//}

これでレイヤーができました！（@<img>{create-layer-3}）

//image[create-layer-3][レイヤーができた！][scale=0.8]{
//}

次はLambda関数を作成しますので、左メニューから［関数］を開いてください。

==== Lambda関数を作成する

［関数の作成］をクリックして、Lambda関数を作ります。（@<img>{create-lambda}）

//image[create-lambda][［関数の作成］をクリックする][scale=0.8]{
//}

関数の作成は次のように入力します。（@<table>{create-app}）

//table[create-app][関数の作成]{
関数名	Bot-Server-on-Lambda
ランタイム	Python 3.10
アーキテクチャ	x86_64
その他の設定	すべてデフォルトのまま
//}

必要事項を入力したら［関数の作成］をクリックします。（@<img>{create-lambda-2}）

//image[create-lambda-2][［関数の作成］をクリックする][scale=0.8]{
//}

これでLambda関数ができました！先に作っておいたレイヤーを選択したいので、［Layers］をクリックします。（@<img>{create-lambda-3}）

//image[create-lambda-3][Lambda関数ができた！][scale=0.8]{
//}

［レイヤーの追加］をクリックします。（@<img>{create-lambda-4}）

//image[create-lambda-4][［レイヤーの追加］をクリックする][scale=0.8]{
//}

レイヤーの選択は次のようにします。（@<table>{select-layer}）

//table[select-layer][レイヤーを選択]{
レイヤーソース	カスタムレイヤー
カスタムレイヤー	Messaging-API-SDK-for-python
バージョン	1
//}

使用するレイヤーを選択したら［追加］をクリックします。（@<img>{create-lambda-5}）

//image[create-lambda-5][［追加］をクリックする][scale=0.8]{
//}

これでレイヤーが追加できました！（@<img>{create-lambda-6}）

//image[create-lambda-6][レイヤーが追加できた！][scale=0.8]{
//}

次はAPI Gatewayを作成しますので、［トリガーを追加］を開いてください。

===={create-api-gateway} API Gatewayを作成する

［ソースを選択］で［API Gateway］を選択します。（@<img>{create-api-gateway}）

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

［トリガー］の中にある［APIエンドポイント］のURLを開くと、AWS Lambdaから［"Hello from Lambda!"］というレスポンスが返ってきます。（@<img>{create-api-gateway-4}）

//image[create-api-gateway-4][［APIエンドポイント］のURLを開くとレスポンスが返ってきた][scale=0.8]{
//}

この［APIエンドポイント］のURLは、後でWebhook URLとして使用します。チャネルアクセストークンやチャネルシークレット同様に、パソコンのメモ帳にしっかりメモしておいてください。

==== Lambda関数で動かすpythonのコードを書く

［"Hello from Lambda!"］というレスポンスが返ってきたのは、［コード］タブのコードソースに次のようなコードが書いてあったからです。（@<list>{default-source-code-1}）

//listnum[default-source-code-1][Lambda関数のデフォルトのコード]{
import json

def lambda_handler(event, context):
    # TODO implement
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
//}

リクエストが来たら、ステータスコード200と共に「Hello from Lambda!」というメッセージを含むJSONを返すようになっています。（@<img>{parrot-bot}）

//image[parrot-bot][ステータスコード200とJSONを返すコード][scale=0.8]{
//}

このコードを、次のようにWebhookを受け取ってオウム返しするコードに書き直してみましょう。

//listnum[source-code-1][AWS Lambdaで動かすpythonのコード][python]{
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
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')

# それぞれ環境変数に登録されていないとエラー
if CHANNEL_SECRET is None:
    logger.error(
        'LINE_CHANNEL_SECRET is not defined as environmental variables.')
    sys.exit(1)
if CHANNEL_ACCESS_TOKEN is None:
    logger.error(
        'LINE_CHANNEL_ACCESS_TOKEN is not defined as environmental variables.')
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

コードを直したら、［Deploy］を押して修正後のコードを反映します。（@<img>{parrot-bot-2}）

//image[parrot-bot-2][［Deploy］を押して修正後のコードを反映する][scale=0.8]{
//}

［関数 Bot-Server-on-Lambda が正常に更新されました。］と表示されたらデプロイ完了です。（@<img>{parrot-bot-3}）

//image[parrot-bot-3][デプロイ完了][scale=0.8]{
//}

==== 環境変数を設定する

コードを動かすには、Messaging APIのチャネルアクセストークンとチャネルシークレットが必要ですが、ソースコードには直接書かず、環境変数として設定して、@<b>{CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')}というように環境変数を参照する形にしています。

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

これでボットサーバーの準備は万端です。LINE Developersコンソールに戻って、Webhook URLの設定をしましょう。

=== Webhook URLを設定する

LINE Developersコンソールを開いて、Messaging APIチャネルの［Messaging API設定］タブにある［Webhook設定］の［Webhook URL］を登録します。［編集］をクリックしてください。@<img>{webhook-url}）

//image[webhook-url][［Webhook URL］の［編集］をクリックする][scale=0.8]{
//}

@<hd>{article02|create-api-gateway}でメモしておいたAPIエンドポイントのURLを貼り付けて、［更新］をクリックしてください。@<img>{webhook-url-2}）

//image[webhook-url-2][APIエンドポイントのURLを貼り付けて［更新］をクリックする][scale=0.8]{
//}

Webhook URLを設定したら、［検証］を押してボットサーバーの動作検証をしてみましょう。@<img>{webhook-url-3}）

//image[webhook-url-3][［検証］を押す][scale=0.8]{
//}

［成功］と返ってきたら、LINEプラットフォームからのWebhookをボットサーバーが受け取って、ちゃんとステータスコード200を返してきています。やりましたね！おめでとうございます。@<img>{webhook-url-4}）

//image[webhook-url-4][［成功］と返ってきたら［OK］をクリックする][scale=0.8]{
//}

ボットサーバーは問題なく動いているようなので、同じ［Messaging API設定］タブにある［応答メッセージ］の［編集］からLINE Official Account Managerを開きます。@<img>{webhook-url-5}）

//image[webhook-url-5][［成功］と返ってきたら［OK］をクリックする][scale=0.8]{
//}

ユーザーがメッセージを送ってきたら、今後はWebhookを受け取ったボットサーバーから応答したいので、［Webhook］をオンにして、代わりに［応答メッセージ］をオフにしてください。@<img>{webhook-url-6}）

//image[webhook-url-6][［成功］と返ってきたら［OK］をクリックする][scale=0.8]{
//}

これでWebhookの設定は完了です。

==={greeting} 友だち追加されたときのあいさつメッセージを併用する

友だち追加されたときに、自動で任意のメッセージを送ることができる「あいさつメッセージ」も、LINE Official Account Managerの［応答設定］でオン、オフの設定ができます。このあいさつメッセージは、Webhookと併用することが可能です。本書では、友だち追加されたときの応答は「あいさつメッセージ」で行い、メッセージが届いたときの応答はボットサーバーから行うので、あいさつメッセージはオンのままで構いません。

なおWebhookのフォローイベント@<fn>{follow}を用いると、「あいさつメッセージ」と同等の処理をボットサーバーでも実現できます。

//footnote[follow][フォローイベント | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#follow-event}]

=== LINE公式アカウントに話しかけてオウム返しを確認しよう

それではLINE公式アカウントに話しかけて、まったく同じメッセージがオウム返しされるか確認してみましょう。@<img>{parrot-reply}）

//image[parrot-reply][メッセージを送ったらオウム返ししてくれた][scale=0.8]{
//}

おめでとうございます！オウム返ししてくれるLINE Botの完成です。

===[column] 【コラム】これは本当にLINEプラットフォームから来たWebhook？

ボットサーバーに、LINEプラットフォームからWebhookが届いたら、その内容に応じて返信を送ったり、何か処理をしたりします。

このとき、届いたリクエストが本当にLINEプラットフォームから届いたWebhookなのか、それともLINEプラットフォームを装った第三者からの攻撃なのか、どうやって判別すればよいのでしょう？

アクセス元のIPアドレスが分かれば、IPアドレス制限をかけることで、LINEプラットフォーム以外からのアクセスを遮断できますが、残念ながらLINEプラットフォームはIPアドレスのレンジを開示していません。@<fn>{ip-addr}代わりに、署名の検証を行いましょう。

LINEプラットフォームから届くWebhookには、そのリクエストヘッダーに必ず「x-line-signature」という署名が含まれています。Messaging APIチャネルのチャネルシークレットを秘密鍵として扱い、届いたWebhookのリクエストボディのダイジェスト値を取得し、さらにそのダイジェスト値をチャネルシークレットを用いてBase64エンコードした値と、リクエストヘッダーのx-line-signatureの署名の一致を確認できれば、これが本当にLINEプラットフォームから届いたWebhookである、というセキュリティの担保ができます。

この検証をしないで、無条件に「テキストメッセージのWebhookイベントが届いたらユーザーに返信する」のような処理をしていると、ボットサーバーに偽のWebhookを投げ続けることで、LINE Botを介して特定のユーザーに大量のメッセージを送りつける攻撃が可能になってしまいます。

署名検証の各言語ごとのコードサンプルは、公式ドキュメントの「署名を検証する@<fn>{signature}」にありますし、SDKを用いることで簡単に検証できます。

===[/column]

//footnote[ip-addr][Webook | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#webhooks}]
//footnote[signature][署名を検証する | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#signature-validation}]

== ChatGPTのAPIを使ったAIチャットボットを作ってみよう

オウム返しが動くとうれしいですね！うれしいものの、「オウム返しされたけど……だからなに？」という気持ちにもなるので、今度はChatGPTのAPIを使って、ちゃんと役に立つAIチャットボットに作り変えてみましょう。

=== ChatGPTとGPT-3.5とは

ChatGPTはOpenAIが提供している対話型のウェブサービスです。このChatGPTの裏側で応答を生成している言語モデルがGPT-3.5です。ユーザーが質問を会話をテキストで送ると、GPT-3.5がその文脈に基づいて応答を生成します。

=== OpenAIに登録してシークレットキーを取得する

OpenAI APIを使用するには、OpenAIの開発者向けサイトに登録して、APIをたたくためのシークレットキーを取得する必要があります。。

OpenAIの公式サイトにアクセスし、［Sign Up］をクリックします。

 * OpenAI
 ** @<href>{https://openai.com/}

アカウント作成のページが表示されたら、ユーザーネーム、メールアドレス、パスワードを入力して登録します。アカウントが作成できると、OpenAIのダッシュボードが表示されます。

［Create a new API key］ボタンをクリックすると、シークレットキー作成のページが表示されるので、APIキー名を入力して［Create API Key］をクリックします。

APIキーが生成されたら、ダッシュボード上に表示されます。このシークレットキーは後ほど使用しますので、パソコンのメモ帳にしっかりメモしておいてください。@<img>{openai-api-keys}）

//image[openai-api-keys][シークレットキーをメモしておく][scale=0.8]{
//}

LINE Developersコンソールで取得したチャネルアクセストークンと同様に、このシークレットキーはOpenAI APIをたたくときに身分証のような役割を果たします。うっかりシークレットキーが載った画面をブログで公開したり、ソースコードに直接書いてGitHubにPushしたりしないように注意してください。

=== OpenAIのSDKを準備する

ChatGPTのAPIをたたくためのOpenAIのSDKも用意されています。先ほどのMessaging APIのSDKと同じようにpython.zipを準備しましょう。

==== OpenAI API SDKのレイヤーを作成する

先ほどのMessaging API SDKと同様に、AWS Lambdaを開いてOpenAI API SDKのレイヤーを作成します。

==== レイヤーを追加する

Lambda関数にOpenAI APIのレイヤーを追加します。

==== Lambda関数のタイムアウトまでの時間を延ばす

Lambda関数の［設定］の［一般設定］からタイムアウトを1分0秒に変更します。

=== AWS LambdaのコードにChatGPTのAPIで質問の回答を取得する処理を追加する

ユーザーの質問に対して、AIチャットボットが自動で応答するようにコードを変更します。さきほど作ったLambda関数のコードを、次のコードに置き換えてください。

//listnum[source-code][AWS Lambdaで動かすpythonのコード]{
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
CHANNEL_SECRET = os.getenv('CHANNEL_SECRET')
CHANNEL_ACCESS_TOKEN = os.getenv('CHANNEL_ACCESS_TOKEN')

# 環境変数からOpenAI APIのシークレットキーを取得する
openai.api_key = os.getenv('SECRET_KEY')

# それぞれ環境変数に登録されていないとエラー
if CHANNEL_SECRET is None:
    logger.error(
        'LINE_CHANNEL_SECRET is not defined as environmental variables.')
    sys.exit(1)
if CHANNEL_ACCESS_TOKEN is None:
    logger.error(
        'LINE_CHANNEL_ACCESS_TOKEN is not defined as environmental variables.')
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

=== LINE公式アカウントに話しかけてAIチャットボットの回答を確認しよう

それではLINE公式アカウントに質問をしてみて、AIチャットボットが回答してくれることを確認してみましょう。

おめでとうございます！これでAIチャットボットの完成です。

===[column] 【コラム】Webhookへのレスポンスが先？応答メッセージが先？

ボットサーバーでWebhookを受け取った際、Webhookのその内容に応じた処理や応答メッセージの送信などをしてからステータスコード200を返す、という順番はお勧めしません。

なぜなら間に挟まる処理や応答メッセージ送信などに時間がかかった場合、レスポンスを返す前にLINEプラットフォームから送られたWebhookのリクエストがタイムアウトしてしまう可能性があるためです。

なんとなく先に色々片付けてからレスポンスを返したい気持ちは分かりますが、郵便局員が郵便物を持って来てくれたとき、わざわざ玄関前で待たせて封筒を開けて中身を読んで、読み終わってから受領の判子を押すのはおかしいよね、と考えると納得しやすいのではないでしょうか。先ずは受領の判子を押して郵便局員を帰らせてあげて、手紙を読んだり、返事を書いたりはそのあとでやりましょう。

またメッセージに対する応答メッセージを送る場合、応答トークンはWebhookを受信後、速やか（具体的には1分以内）に使う必要があります。@<fn>{reply_token_rule}Webhook受信後、すぐに返信を送れる場合は応答メッセージで構いませんが、色々な処理を行ってかなり時間が経ってから返信したい場合は、応答トークンが既に無効になっている可能性があります。その場合は、対象となる友だちのユーザーIDを指定したプッシュメッセージで返信を送ることが可能です。

===[/column]

//footnote[reply_token_rule][応答トークン | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#send-reply-message-reply-token}]
