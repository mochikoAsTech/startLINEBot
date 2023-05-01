= はじめに

//flushright{

2023年5月
mochikoAsTech

//}

この本を手に取ってくださったあなた、こんにちは、あるいははじめまして。「LINE Botをつくってみよう ～APIを試して学んでしっかりわかる～」の筆者、mochikoAsTechです。

いきなりですが、プログラムを書いたことはありますか？自分の書いたプログラムを動かしてみて、ブラウザで結果が表示されたときの「う、動いたー！」という喜びっていいですよね。まだ書いたことがない、という人には「あれはいいものだぞ！」とお勧めしておきます。

真っ白い背景に黒字で@<ttb>{Hello World!}と表示されただけでも「自分が作ったものがいつも使っているブラウザで動いたー！」という喜びでいっぱいになるのに、それが「自分が作ったものがいつも使っているLINEで動いた！」になるとますます嬉しいので、筆者ははじめてプログラミングをやってみるならLINE Botを題材にするのはなかなかよい選択じゃないかと思っています。無料ではじめられるし、たぶんあなたが思ってるより少ない手順であっさり動きます。それでいてこだわろうと思ったら色んな奥深い機能があって飽きないし、ドキュメントが日本語であるし、コミュニティも活発で質問や相談がしやすいです。

あ、それからいま色んなところで話題になっているChatGPTも触ってみたいと思いませんか？なんかすごいらしいし、ちょっと気になっている…それなら「気になっている」まま時間が経ってしまうともったいないので、ここでガッと触ってみましょう。他人が触った話を聞いたり読んだりするのもいいですが、やっぱり自分で触ってみると情報量も理解度も格段に違います。「やってみようかな」や「やってみたいな」という衝動は、生まれた瞬間にグッと掴んで躊躇わずそのまま飛び込んでみると楽しいですよ！

あなたも本書で「気になっていたChatGPTを使ってAIチャットボットが作れた！自分が作ったものがLINEで動いた！」という喜びを味わってみませんか？大事なのは勢いです。「つっこむぞ、つかまれ！」という気持ちではじまりはじまりー！

== 想定する読者層

本書は、こんな人に向けて書かれています。

 * 「APIをたたく」をやってみたい人
 * 「チャットボットを作る」をやってみたい人
 * これからプログラミングを学ぼうと思っている人
 * LINE APIを使ってみたい人
 * ChatGPTやGPT-3.5、GPT-4が気になっている人
 * LINE公式アカウントの運用をしている人
 * LINEのMessaging APIがどういうものか知らない人

== マッチしない読者層

本書は、こんな人が読むと恐らく「not for meだった…（私向けじゃなかった）」となります。

 * コミュニケーションアプリ「LINE（ライン）」を使ったことがなく、LINEの基本操作から知りたい人
 * LINE公式アカウントで友だちをうまく増やす広告や宣伝の方法を知りたい人

== 本書の構成

本書は、@<chapref>{article01}でLINE公式アカウントについて解説し、@<chapref>{article02}で実際にLINE Botをつくって動かし、最後に@<chapref>{article03}でLINE Botを育てていく色んな可能性を紹介する、という三部構成になっています。

== 本書の特徴

実際にLINE公式アカウントからメッセージを送ったり、オウム返しするLINE BotやAIチャットボットを作ったりします。手を動かして試してから裏付けとなる事柄を学ぶ、というステップを交互に踏むため、理解がしやすく、プログラミング初心者でも飽きずに読み進められる内容です。

また実際の開発でありがちなトラブルをとり上げて、

 * こんなエラーが起きたら原因はどう調べたらいいのか？
 * 問題をどう解決したらいいのか？
 * どうしたら事前に避けられるのか？

を解説しています。

紙の書籍をお買い上げいただいた方は、フルカラーのPDF版を無料でダウンロードできますので、ぜひご活用ください。詳しくは@<chapref>{postscript}にある@<hd>{postscript|pdf}を参照してください。

== 用語の定義

私たちは「LINE（ライン）」という言葉を、無意識に色んな意味で使っています。

「LINEってやってる？」「うん。でも家族としか使ってない」というときのLINEは、コミュニケーションアプリとしてのLINEアプリのことを指しています。「昨日送ったLINE見た？」「ごめん。寝てた」というときのLINEは、LINEアプリのトーク上でやりとりするメッセージのことを指しています。「LINEのオフィスってカフェがあるらしいよ」「いいねー」というときのLINEは、LINE株式会社のことを指しています。その他にもLINE PayやLINE MUSICといったさまざまなLINE関連サービスや機能が、略称としてLINEと呼ばれているケースもあります。

こんなふうに、同じ「LINE」という言葉でも文脈によって色んな意味になるため、本書における用語を最初に定義しておきます。

 * 本書では、LINEアプリのことを「LINE」と呼びます。ただ「LINE」とだけ書いてあったら、これはLINEアプリのことだな、と思ってください。
 * LINEアプリのトーク上でやりとりするメッセージのことは、「メッセージ」と呼びます。
 * 会社としてのLINEは、「LINE株式会社」と呼びます。
 * それ以外の各サービスは「LINE Pay」や「LINE MUSIC」のような正式名称で呼びます。

//pagebreak

== 用意するもの

 * LINEがインストールされたスマートフォン
 * パソコン（WindowsまたはMac）

== 本書のゴール

本書を読み終わると、このような状態になっています。

 * LINE公式アカウントについて一通りの知識がある
 * LINE Botが動く仕組みを理解している
 * LINE Botを作るときに何を準備すればいいか分かっている
 * WebhookとAPIの違いが分かっている
 * プロバイダーやチャネルに何を登録すべきか分かっている
 * 読む前よりLINE APIが好きになっている

== 免責事項

本書に記載された社名、製品名およびサービス名は、各社の登録商標または商標です。本書において操作説明のために載せている各画面のスクリーンショットは、著作権法第32条引用および過去の判例に従い、出典元を明記した上で、必然性のある箇所でのみ、引用と分かる形で掲載しています。

本書の発刊時点で筆者はLINE株式会社に所属していますが、本書は個人として執筆したものであり、本書に記載されている内容はいずれも所属する組織の公式見解ではありません。また、本書は一般に開示されている情報を元に書かれており、筆者が所属する組織において知り得た情報は含まれていません。LINE APIについて言及するにあたって、所属を隠した宣伝であると誤解されないよう所属組織をここに明記しておきます。

本書はできるだけ正確を期すように努めましたが、筆者が内容を保証するものではありません。よって本書の記載内容に基づいて読者が行なった行為、及び読者が被った損害について筆者は何ら責任を負うものではありません。

不正確あるいは誤認と思われる箇所がありましたら、必要に応じて適宜改訂を行いますのでGitHubのIssueやPull requestで筆者までお知らせいただけますと幸いです。

@<href>{https://github.com/mochikoAsTech/startLINEBot}
