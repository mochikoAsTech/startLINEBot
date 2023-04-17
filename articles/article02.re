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

== Messaging APIでボットを作ろう

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

== LINE Official Account ManagerでMessaging APIチャネルを作る

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

== Messaging APIでメッセージを送信してみる

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

チャネルアクセストークンも手に入ったし、早速Messaging APIでメッセージを送ってみましょう。

=== Messaging APIでブロードキャストメッセージを送信する

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

== LINE公式アカウントから返信する

さて、ここまでは「LINE公式アカウントからメッセージを送る」という、LINE公式アカウント起点の話をしてきました。LINE公式アカウント起点というのは、たとえば今月の定休日を知らせるメッセージを送るとか、新商品が出たときにメッセージを送るとかいうように、LINE公式アカウント側が「送りたい！」と思った任意のタイミングでメッセージを送る、ということです。

でも片方が話したいときだけ一方的に話すのでは、それは対話とは言えません。ユーザーが友だち追加してくれたときや、ユーザーが何か質問してきたとき、ユーザーがリッチメニュー@<fn>{rich}をタップしたときなど、ユーザー起点のコミュニケーションにきちんと反応できるようになってこそのチャットボットです。

//footnote[rich][リッチメニューについては、@<hd>{article02|richmenus}で後述します。]

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

== ボットサーバーを作ってみよう

今回はWebhookを受け取って、200を返して、応答メッセージを送るボットサーバーとして、AWSのサーバーレスサービス、AWS Lambda@<fn>{aws-lambda}を使用します。

//footnote[aws-lambda][AWSアカウントの作成方法は「DNSをはじめよう」で、またAWSとは何かについての説明や、無料利用枠の範囲、利用金額が一定額を超えたらアラートが飛ぶようにする設定などは「AWSをはじめよう」で詳しく紹介しています。もしまだAWSのアカウントをお持ちでない場合は、そちらを参考にしてください。 @<href>{https://mochikoastech.booth.pm/}]

=== AWS LambdaとAPI Gatewayでボットサーバーを作る

AWS LambdaとAPI Gatewayを組み合わせて、ボットサーバーを用意し、そのURLをWebhook URLとして登録します。（要追記）

Messaging APIでは、開発をサポートするSDKがJava、PHP、Go、Perl、Ruby、Python、Node.jsで用意されています。今回はPythonのSDKを使ってコードを書いていきます。

 * @<href>{https://github.com/line/line-bot-sdk-python}

 1. mkdir python
 1. cd python
 1. pip install line-bot-sdk -t . --no-user
 1. SDKのコードが詰まったpythonディレクトリをzipファイルに圧縮する
 1. AWS Lambdaで「レイヤーを作成」
 1. zipファイルを選択
 1. 互換性のあるランタイムでPython 3.9を選択する
 1. x86_64にチェックを入れる
 1. カスタムレイヤーで選ぶ
 1. APIタイプはHTTP APIでAPI gatewayを作る
 1. Lambdaの設定>一般設定からタイムアウトを1分0秒に変更する

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

この後、LINE Developersコンソールの「Webhook URL」でボットサーバーのURLを登録するため、用意したAPI Gateway）のURLをコピーしておきましょう。

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

=== ボットサーバーをWebhook URLに登録する

再びLINE Developersコンソールを開いて、作成したボットサーバーのURLをWebhook URLに登録します。

チャネルアクセストークンとチャネルシークレットをコピーして、AWS Lambdaの環境変数に登録します。

=== ユーザーのメッセージをオウム返しする

それではLINEでLINE公式アカウントにメッセージを送って、そのメッセージがオウム返しされて戻ってくるか、確認してみましょう。（要追記）

=== OpenAI APIのシークレットキーを取得する

OpenAIの開発者登録をして、シークレットキーを取得します。

=== AIチャットボットでユーザーの質問に自動応答する

ユーザーの質問に対して、AIチャットボットが自動で応答するようにコードを変更します。

===[column] 【コラム】Webhookへのレスポンスが先？応答メッセージが先？

ボットサーバーでWebhookを受け取った際、Webhookのその内容に応じた処理や応答メッセージの送信などをしてからステータスコード200を返す、という順番はお勧めしません。

なぜなら間に挟まる処理や応答メッセージ送信などに時間がかかった場合、レスポンスを返す前にLINEプラットフォームから送られたWebhookのリクエストがタイムアウトしてしまう可能性があるためです。

なんとなく先に色々片付けてからレスポンスを返したい気持ちは分かりますが、郵便局員が郵便物を持って来てくれたとき、わざわざ玄関前で待たせて封筒を開けて中身を読んで、読み終わってから受領の判子を押すのはおかしいよね、と考えると納得しやすいのではないでしょうか。先ずは受領の判子を押して郵便局員を帰らせてあげて、手紙を読んだり、返事を書いたりはそのあとでやりましょう。

またメッセージに対する応答メッセージを送る場合、応答トークンはWebhookを受信後、速やか（具体的には1分以内）に使う必要があります。@<fn>{reply_token_rule}Webhook受信後、すぐに返信を送れる場合は応答メッセージで構いませんが、色々な処理を行ってかなり時間が経ってから返信したい場合は、応答トークンが既に無効になっている可能性があります。その場合は、対象となる友だちのユーザーIDを指定したプッシュメッセージで返信を送ることが可能です。

===[/column]

//footnote[reply_token_rule][応答トークン | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#send-reply-message-reply-token}]

===[column] 【コラム】メッセージの通数はどうカウントされるのか

たとえば1人の友だちに対してLINE公式アカウントから、こんなふうにテキストと画像とスタンプという3つのメッセージオブジェクトが含まれるメッセージを送った場合、メッセージの通数は1通でしょうか？それとも3通でしょうか？（@<img>{three-message-objects}）

//image[three-message-objects][テキストと画像とスタンプのメッセージ][scale=0.6]{
//}

メッセージの通数は、送信対象となった友だちの人数でカウントされますので、このように3つのメッセージオブジェクトをまとめて送った場合のカウントは1通となります。もしテキストを送る、画像を送る、スタンプを送る、というように3回に分けて送るとカウントは3通になります。ちなみにメッセージオブジェクトはLINE Official Account Managerや管理アプリでは最大3つ、Messaging APIでは最大5つまで指定できます。

メッセージは友だちとLINE公式アカウントの1対1のトークだけでなく、何人もの友だちが参加しているグループトークに対しても送信可能です。前述のとおり、メッセージの通数は送信対象となった友だちの人数でカウントされますので、友だち3人とLINE公式アカウントが参加しているグループトークに、LINE公式アカウントからメッセージを送った場合、メッセージ通数は3通としてカウントされます。

なおどんなメッセージでも無料メッセージの通数を消費する訳ではありません。友だち追加されたときのあいさつメッセージや、Webhookに含まれる応答トークンを使って送る応答メッセージなどは、何通送っても通数としてカウントされません。@<fn>{free-message}

===[/column]

//footnote[free-message][課金対象となるメッセージについて｜LINE for Business @<href>{https://www.linebiz.com/jp/service/line-official-account/plan/}]

=== エラーの統計情報

ボットサーバーでWebhookを受け取って、きちんとステータスコード200が返せなかった場合、エラーの統計情報でそのログが確認できます。（要追記）

 * @<href>{https://developers.line.biz/ja/docs/messaging-api/receiving-messages/#error-statistics-aggregation}

=== ボットサーバーがWebhookを受け取れなかったときの再送機能

たとえばLINE公式アカウントが急に有名になり、一気に友だちが増えて、メッセージが大量に送られてきたとします。急なアクセス集中でサイトが落ちるように、LINEプラットフォーム飛んでくるWebhookのリクエストによって、ボットサーバーが過負荷になって応答できなくなってしまったらどうなるのでしょうか。

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

これを防ぐためには、ボットサーバー側で商品購入処理を行う際に、Webhookのイベントごとに一意な値であるwebhookEventIdを確認して、「既に購入処理を行ったWebhookイベントと同一のイベントではないか？」を確認する必要があります。

Webhookの再送は便利な機能ですが、このように意図しない再送が行われたときのことを考えた重複チェックの処理がなければ、迂闊にオンにするべきではありません。

==={greeting} 友だち追加されたときのあいさつメッセージ

友だち追加されたときに、自動で任意のメッセージを送ることができる「あいさつメッセージ」は、LINE Official Account Managerの［応答設定］でオン、オフの設定ができます。Webhookに対するボットサーバーからの応答と、このあいさつメッセージを併用することも可能です。

Webhookのフォローイベント@<fn>{follow}を用いると、「あいさつメッセージ」と同等の処理をボットサーバーで実現できます。

//footnote[follow][フォローイベント | LINE Developers @<href>{https://developers.line.biz/ja/reference/messaging-api/#follow-event}]

=== ユーザーIDを指定して特定の人に送る

Messaging APIでメッセージを送るとき、いちばん簡単なのは友だち全員にメッセージを一斉配信するブロードキャストメッセージです。しかしユーザーのユーザーIDが取得できたら、そのユーザーIDを指定して、特定の人にだけメッセージを送ることも可能です。特定のひとりにだけ送りたいときはプッシュメッセージ、特定の数人にまとめて送りたいときはマルチキャストメッセージで送れます。（要追記）

===[column] 【コラム】開発チームだけにメッセージのテスト配信がしたい
     
たとえば本番用のLINE公式アカウントと、テスト用のLINE公式アカウントを別々に用意しておいて、開発チームのメンバーだけがテスト用のLINE公式アカウントと友だちになることで、本番配信前のメッセージのテスト配信と確認を実現していたとします。

この場合、開発チームに所属していたメンバーがAさん、Bさん、Cさんの中でCさんが退職してしまうと、残ったAさん、Bさん側でCさんをテスト用のLINE公式アカウントの友だちからブロックする方法がありません。退職前にCさんに頼んで、Cさん側からテスト用のLINE公式アカウントをブロックしてもらうしかないのです。

さらに厳密に言うと、一度Aさん、Bさんの目の前でCさんにブロックの操作をしてもらったとしても、Cさんの操作でブロックは解除できるので、悪意のあるCさんが後日ブロックを解除してしまうことはとめられません。こうなると、退職したCさんにも、発売前の商品や未発表の情報を含むテスト配信のメッセージが届き続けてしまいます。

なのでテスト配信の仕組みは、「一度友だち追加されたら、開発者側からは友だち状態はコントロールできない」という前提で組んでおく必要があります。

たとえば、テスト配信のメッセージはテスト用のLINE公式アカウントから送るとしても、ブロードキャストメッセージで友だち全員に送るのではなく、開発チームのAさん、Bさん、CさんのユーザーIDを指定したマルチキャストメッセージを送る、という方法がお勧めです。これならCさんの退職後、開発チームに残ったAさんBさんが送信対象からCさんのユーザーIDを消せば、Cさんには公開前のテストメッセージは届かなくなります。

===[/column]

=== メッセージの配信対象を属性で絞り込む

ナローキャストメッセージで、性別や年齢、地域、友だちになってからの期間といった属性情報を指定して送ることも可能です。（要追記）

=== メッセージ送信元のアイコンと表示名を変更する

メッセージを送るときに、送信元のアイコンと表示名を変更して送ることができます。たとえばテーマパークのLINE公式アカウントで、特定のキャラクターにちなんだイベントを告知するときだけ、メッセージの送信元をそのキャラクターのアイコンと名前にする、といった使い方が可能です。（要追記）

 * @<href>{https://developers.line.biz/ja/docs/messaging-api/icon-nickname-switch/}

===[column] 【コラム】URLを送る前にOGPの見た目を事前に確認したり、キャッシュを消したりしたい

LINEでURLを含むメッセージを送ると、こんなふうにプレビューが表示されます。（@<img>{url-preview}）

//image[url-preview][URLのプレビュー][scale=0.4]{
//}

実際にメッセージを送る前に、このプレビューでどんな画像やテキストが表示されるのか、確認したかったらどうすればいいのでしょう？

実はPagePokerという公式のツールを使うと、対象ページのOGPタグ@<fn>{ogp}を読み込んで、どんなふうにプレビューが表示されるのかを事前に確認できます。@<fn>{card-validator}

 * Pagepoker @<href>{https://poker.line.naver.jp/}

「Clear Cache」にチェックを入れることで、LINE側サーバーのキャッシュも削除できるということなので、ウェブサイト側でOGPの画像を差し替えた後にここでキャッシュを削除すれば、「URLを投げたらうっかり古い画像がプレビューで表示されてしまった」という事態も避けられます。

OGPタグの書き方については、LINE Developersサイトの「トークとLINE VOOM内のURLプレビューはどのようにして生成されますか？」を参考にしてください。

 * @<href>{https://developers.line.biz/ja/faq/#how-are-the-url-previews-generated}

===[/column]

//footnote[ogp][OGPはOpen Graph Protcolの略です。HTMLにメタデータとして「og:image」のようなOGPタグを書いておくことで、TwitterやLINEなどでそのURLを共有したときに、URLそのままではなく対象ページのタイトルや概要、画像などがカードのように表示されます。]
//footnote[card-validator][TwitterのCard Validatorとか、Facebookのシェアデバッガーみたいなものですね。Card Validatorは気づいたらプレビュー確認機能がなくなっていたけれど。 @<href>{https://cards-dev.twitter.com/validator} @<href>{https://developers.facebook.com/tools/debug/}]

=== Flex Messageで見た目にこだわったメッセージを送る

レイアウトを自由にカスタマイズできるFlex Messageなら、見た目にこだわったメッセージが送れます。（要追記）

そしてFlex Message Simulator（ログイン必須）を使えば、JSONのコードを自分で書かなくてもFlex Messageが作れます。

 * Flex Message Simulator
 ** @<href>{https://developers.line.biz/flex-simulator/}

ただしFlex Message Simulatorで出力されるJSONは、messages直下のFlex Message全体じゃなくて、コンテナ（contents以下）なので注意が必要です。

=={richmenus} リッチメニュー

LINE公式アカウントと友だちになると、トーク画面の下部にこんなメニューが表示されます。テキストだけでなく、画像でできた贅沢な多彩なメニュー…つまりリッチなメニュー…リッチなメニューなので…リッチメニュー！そう、これがリッチメニューです。わぁ、リッチ！（@<img>{richmenu}）

//image[richmenu][リッチメニュー][scale=0.4]{
//}

このリッチメニューは、一番下の「メニュー」と書いてあるバーをタップすることで閉じたり開いたりできます。このバーのテキストも、デフォルトの「メニュー」から「メニューはこちら」「お問い合わせの入力はこちら」「ほっとするブレイクタイムを」「会員証」「お役立ち情報はこちら」「人気ランキングをチェック！」「こちらもチェック」「荷物の追跡・再配達・集荷受付」といった様々なテキストに変更できます。

リッチメニューの実態は1枚の画像であり、画像内の各領域にそれぞれリンクを設定することで、公式サイトや予約ページ、特定の機能などにユーザーを誘導できます。

=== リッチメニュープレイグラウンドでリッチメニューを体験してみる

リッチメニューの様々な機能は、文字で説明するより体験してみるのが一番分かりやすいです。公式で提供されているリッチメニュープレイグラウンドという、「リッチメニューを体験するためのLINE公式アカウント」と友だちになってみましょう。（@<img>{richmenu-playground-qrcode}）

//image[richmenu-playground-qrcode][リッチメニュープレイグラウンドと友だちになる][scale=0.4]{
//}

「リッチメニューを開く」をタップすると、「メッセージアクションを試す」と表示されます。これは「ユーザーがリッチメニューをタップすることで、特定のメッセージをユーザーから自動送信させる」という機能です。早速試してみましょう。

あなたが入力した訳でも送った訳でもないのに、「message sent successfully!」というメッセージがあなたから送信されました。これがメッセージアクションです。メッセージアクションによって、ユーザーからLINE公式アカウントに対してメッセージが送られ、それによってこんなWebhookがボットサーバーに届きましたよ、というのを解説してくれています。

たとえば「再配達の申し込みをしたかったら、LINEで『再配達』というメッセージを送ってね」のように、ユーザーに手入力を促さなくても、リッチメニューに「再配達の申し込み」というボタンを用意して、そのボタンの領域をタップしたら「再配達」というメッセージが自動送信されるよう、対象の領域にメッセージアクションを設定しておけばいいのです。

=== リッチメニューの画像を作る

LINE Official Account Managerでリッチメニューの作成画面を開くと、「デザインガイド」というボタンがあり、そこからリッチメニューのテンプレート画像がダウンロードできます。本書ではこのテンプレートをそのまま使ってリッチメニューを設定してみます。

リッチメニューの画像は、LINE Official Account Managerで作成することも可能ですし、Canvaなどで自作しても構いません。サイズの制約は横幅が800px以上2500px以下、高さが250px以上となっています。参考までに3マスが2段重ねで6マス分のテンプレート画像だと横幅が2500px、高さが1686pxで作られていました。（要追記）

=== LINE Official Account ManagerとMessaging APIでのリッチメニューの制約の違い

リッチメニューはMessaging APIで頑張ってJSONを組み立てて作らなくても、実はLINE Official Account Managerという管理画面上で、GUIでぽちぽち作ることも可能です。

前述のあいさつメッセージのように、GUIのLINE Official Account Managerと、CUIのMessaging APIは、どちらか一方しか使えないというものではなく、リッチメニューはLINE Official Account Managerで設定し、メッセージの送信はMessaging APIを使う、というように機能によって使い分けが可能です。

ただし、LINE Official Account Managerでは大が7種類、小が5種類という特定のサイズと形からしか選べません。また全員に同じリッチメニューを出す機能しかないため、会員証を持っている人にだけ会員向けのリッチメニューを出す、といった出し分けもできません。Messaging APIであれば、縦横のサイズや、それぞれの領域も自由に設定でき、ユーザーごとに別々のリッチメニューを表示させることも可能です。Messaging APIなら、タブ切り替えのようなリッチメニューを作ることもできます。

限定された機能で構わないのでGUIの管理画面からラクに設定したいならLINE Official Account Managerを使えばいいし、色んな機能を使い倒して限界まで自由にやりたいのであれば、Messaging APIを使って自分だけの管理画面を作るのがオススメです。

=== リッチメニューを設定する

リッチメニューは3つのステップで設定します。

 1. リッチメニューを作る
 2. そのリッチメニューに画像をアップロードする
 3. それをデフォルトのリッチメニューとして設定する

=== リッチメニューの設定方法と表示の優先順位

リッチメニューには以下の3つがあり、複数設定されていた場合は、上から順に優先的に表示されます。

 1. Messaging APIで設定するユーザー単位のリッチメニュー
 1. Messaging APIで設定するデフォルトのリッチメニュー
 1. LINE Official Account Managerで設定するデフォルトのリッチメニュー

== Messaging APIをもっと楽しむために

ここまでMessaging APIを使ってLINE Botを作ってきましたが、はじめてのチャットボット作りは楽しんでもらえましたか？

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

LINE Creative Labを使うと、画像メッセージとして送れる素材が簡単に作れます。

 * LINE Creative Lab
 ** @<href>{https://creativelab.line.biz/}

=== PC版のLINEを使おう

スマートフォンのLINEと同じアカウントで、PC版のLINEも使えます。メッセージの確認などはPC版のLINEでやると便利です。ただしリッチメニューなど、PC版のLINEではサポートされていない機能も一部ありますのでご注意ください。

 * パソコンでLINEを利用する｜LINEみんなの使い方ガイド
 ** @<href>{https://guide.line.me/ja/services/pc-line.html}

=== LINE Developers communityに参加しよう

LINE APIを活用している有志によって、LINE Developers communityのイベントが定期的に開催されています。LINE API Expertとして認定されたみなさんが、最新機能や開発手法をオンラインで教えてくれるので、ひとりで悩まずにコミュニティに参加してみるのがお勧めです。LINE Developers communityのサイトにはユーザー同士のQ&Aもあり、開発でつまづいたときは質問を投稿したり、過去の質問からヒントを探したりできます。

 * LINE Developers community
 ** @<href>{https://www.line-community.me/}
