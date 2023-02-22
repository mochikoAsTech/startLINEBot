= LINE Botをつくってみよう ～ひとつずつAPIを試して学んでしっかりわかる～

== 用語の定義

気づいていないかもしれませんが、実は私たちは「LINE（ライン）」という言葉を、無意識に色んな意味で使っています。

「LINEってやってる？」「うん。でも家族としか使ってない」というときのLINEは、コミュニケーションアプリとしてのLINEアプリのことを指しています。

「昨日送ったLINE見た？」「ごめん。寝てた」というときのLINEは、LINEアプリのトーク上でやりとりするメッセージのことを指しています。

「LINEってヤフーと経営統合したんでしょ」「そうなんだ」というときのLINEは、LINE株式会社のことを指しています。

「お支払いは何になさいますか？」「あ、LINEで！」というときのLINEは、スマホで送金や決済ができるLINE Payというサービスを指しています。

こんなふうに、同じ「LINE」という言葉でも文脈によって色んな意味になるため、本書での用語定義を最初にお伝えしておきます。

 * 本書では、LINEアプリのことを「LINE」と呼びます。ただ「LINE」とだけ書いてあったら、これはLINEアプリのことだな、と思ってください。
 * LINEアプリのトーク上でやりとりするメッセージのことは、「メッセージ」と呼びます。
 * 会社としてのLINEは、「LINE株式会社」と呼びます。
 * それ以外の各サービスは「LINE Pay」のような正式名称で呼びます。

== Messaging APIとは

=== 開発には「個人のLINEアカウント」が必要か？

=== ビジネスアカウントの制限

== LINE公式アカウントとは

服屋さんのレジで「LINEで友だちになると5%オフになるクーポンがもらえるんですが、よかったらどうですか？」と声をかけられたり、カフェでテーブルの上に「友だち追加するとワンドリンク無料！」と書かれたポップが置いてあるのを見たことはありませんか？

普段、あなたはLINEで友だちとメッセージや写真をやりとりしていると思います。実在する人間の友だちとやりとりするのと同じように、LINEでは企業や店舗とやりとりできます。この企業や店舗のアカウントは、普通のLINEアカウントとは異なる「LINE公式アカウント」と呼ばれています。

LINE公式アカウントは、企業や店舗だけでなく、芸能人のものも存在します。たとえば地震のときに誰よりも早く「大丈夫？」とメッセージをくれて、彼氏感がすごい、と話題になった佐藤健さんのアカウントもLINE公式アカウントです。あまりのプライベートっぽさに、普通にLINEで友だちになったような感覚になりますが、落ち着いてください。あれはLINE公式アカウントです。

以前の「LINE@（ラインアット）」という名称の方が見覚えがある、という人も居るかもしれません。LINE@は2019年4月18日にLINE公式アカウントへ統合されたのですが、いまだにLINE@の名前で友だちを募集している店頭ポスターを見ることも少なくありません。@<fn>{lineat}

//footnote[lineat][LINE@サービス統合および移行について @<href>{https://d.line-scdn.net/stf/line-lp/migrationinfomation-LINEAT190718.pdf}]

このLINE公式アカウントは、企業や店舗などの法人、あるいは芸能人だけでなく、誰でも、つまりあなたでも無料ですぐに作ることができます。

=== LINE公式アカウントにかかる費用

LINE公式アカウントは、以下の3つのプランがあります。

 * コミュニケーションプラン（0円。無料メッセージは200通/月）
 * ライトプラン（月額5,000円。無料メッセージは5,000通/月）
 * スタンダードプラン（月額15,000円。無料メッセージは30,000通/月。さらに追加メッセージは1通3円）

2023年5月31日までは、フリープラン、ライトプラン、スタンダードプランの3種類でしたが、2023年6月1日からフリープランの名称がコミュニケーションプランに代わり、それぞれのプランで送れる無料メッセージの通数も変わりました。@<fn>{tbf14}

//footnote[tbf14][本書が出る技術書典14の開催期間（2023年5月20日から2023年6月4日）の途中でちょうどプランが変わるので、ここでは分かりやすく、「今日は2023年6月1日以降だ！」という認知で進みます。2023年5月に本書を読んでいるみなさん、いいですか、いまは6月1日以降です。もうプランは変わったのです。]

@<href>{https://www.linebiz.com/jp/news/20230125/}

たくさんのメッセージを継続して送ろうとすると費用がかかりますが、試しにちょっと開発してみる程度なら無料のフリープランで収まりますし、無料メッセージの通数を使い切れば、次の月初までメッセージが送れなくなるだけです。自分で有料のライトプランやスタンダードプランに申し込まない限り、メッセージの使いすぎで勝手に課金が始まることはありませんので安心してください。

=== LINE公式アカウントと普通のLINEアカウントとの違い

LINE公式アカウントと普通のLINEアカウントは、どうやって見分けがつくのでしょうか？運用している本人にはもちろん分かりますが、どちらもQRコードを読み込んで友だち追加する形なので、友だちになる側はどこで「あ、これLINE公式アカウントだ」と気づけるのでしょう？（@<img>{line-official-account}）

左がLINE公式アカウントで、右が普通のLINEアカウントです。

普通のLINEアカウントには、追加、ブロック、通報のボタンが並んでいますが、LINE公式アカウントには追加、投稿、が並んでいます。またLINE公式アカウントの方は、ベーシックIDが表示されていたり、「ほかの公式アカウントを見る」とあったり、「友だち限定の情報をゲット」と出ているので、ちょっと変な感じがしますね。

//image[line-account][LINEアカウント][scale=0.4]{
//}

//image[line-official-account][LINE公式アカウント][scale=0.4]{
//}

== LINE公式アカウントを作ってみよう

LINE公式アカウントを作る経路は、以下の4つがあります。どれで作っても同じ「LINE公式アカウント」ができます。

 * LINEで作る
 * LINE公式アカウント管理アプリで作る
 * LINE Official Account Managerで作る
 * LINE Developersコンソールで作る

そう、なんと専用のアプリや管理画面を使わなくても、お手持ちのLINEで作れるんです！

=== LINE公式アカウントを作ってみる

下に並んでいるホーム、トーク、VOOM、ニュース、ウォレットという5つのメニューのうち、中央にある［VOOM］をタップしてください。VOOMとやらがなんなのかということはいまは考えてはいけません。きっとショート動画のプラットフォーム的な何かです。

そして右上にある人型のアイコンをタップします。

［自分の公式アカウント］の下にある［公式アカウント作成・連携］というボタンをタップします。

もし［公式アカウントを作成するか、既存アカウントを連携するには、メールアドレスを登録してください］と表示されたら、あなたはまだLINEアカウントにメールアドレスを登録していないようです。そのまま［登録］をタップして、メールアドレスを登録してください。入力したメールアドレス宛てに［[LINE] メールアドレス登録確認メール］という件名のメールが届くので、そこに書いてある4桁の認証番号を、LINEの［メール認証］の画面で入力します。これでメールアドレスの登録が完了しました。改めて、［公式アカウント作成・連携］というボタンをタップしてください。@<fn>{mail}

//footnote[mail][登録したメールアドレスを変更したい場合は、下に並んでいる［ホーム］から右上の歯車アイコンをタップして［設定］を開き、［アカウント］の［メールアドレス］で変更できます。]

［LINE公式アカウントを作成］を再びタップします。

プロフィール画像とアカウント名を設定します。アカウント名と言われてもピンとこないかもしれませんが、もしあなたが技術書典に出展しているサークルさんなら、サークルの名前とアイコンを設定して、サークルの宣伝をするLINE公式アカウントにしてもいいかもしれません。

カテゴリーの大業種は［個人］を選ぶと、小業種に［個人（芸術・創造・執筆）］があります。私はサークルの宣伝用という位置づけで作るので、この小業種にしますが、他にも［個人（IT・コンピュータ）］や［個人（学生）］、［個人（その他）］などもあるので、個人的に開発を試す用途など、LINE公式アカウントの使い道に応じて適していると思われる業種を選択してください。

［会社・事業者の所在国・地域］は、個人の場合は店舗や居住地を選択してください、と書いてあったので、［日本］を選びます。

下部に表示されている［LINE公式アカウント利用規約］と［LINEビジネスID利用規約］はしっかり読んで@<fn>{readtoc}、同意できることを確認してから［アカウントを作成］をタップします。

//footnote[readtoc][全部入力してから利用規約を開いて読み、Androidの戻るボタンで戻ったら、入力した項目が全部消えていた。まじか。]

いくつか同意の必要なページが出てきます。まず［情報利用に関する同意について］です。内容をよく読んで同意できることを確認してから［同意する］をタップします。

LINE公式アカウントができました！どうやらこれで、作ったLINE公式アカウントからLINE VOOMに動画が投稿できるようです。友だちに限定せず、全体に向けて動画でアピールしたいときはこれでよさそうです。でも友だち追加してくれた相手にトークでメッセージが送りたいときはどうすればいいのでしょう？

=== スマートフォンにLINE公式アカウント管理アプリをインストールする

作ったLINE公式アカウントからメッセージを送るため、既にLINEを使っているスマートフォンで、LINE公式アカウント管理アプリをインストールします。

 * Android
 ** LINE公式アカウント
 ** https://play.google.com/store/apps/details?id=com.linecorp.lineoa
 * iOS
 ** LINE公式アカウント
 ** https://apps.apple.com/jp/app/id1450599059

インストールしたLINE公式アカウント管理アプリを開いて、［LINEアプリで登録・ログイン］をタップします。

先ほどLINE公式アカウントを作成するときに確認を求められた、［LINEビジネスID利用規約］への同意が再び求められます。問題なければ［ログイン・登録］をタップします。

するとLINE公式アカウントの管理アプリに対して、LINEで自分が登録しているプロフィール情報を提供して良いか、という認証画面が表示されます。問題なければ［許可する］をタップします。もしここで許可した情報提供を、後で取り消したくなった場合は、LINEの［設定］から［アカウント］を開いて、［連動アプリ］で確認したり、取り消したりできます。

出てきたー！さっき作ったLINE公式アカウントが、管理アプリで表示されました！

早速、［メッセージを配信する］をタップして、メッセージを送ってみましょう。

［追加］をタップして、先ずは［テキスト］を選び、適当なテキストを入力します。さらに［追加］をタップして、今度は［スタンプ］を選び、［スタンプを選択］から適当なスタンプを選びます。これでどんなメッセージが送られるのか、右上の［プレビュー］から確認してみましょう。

［トークルーム］では、こんな感じの見た目になるようです。［トークリスト］をタップすると、トークの一覧画面での見え方も確認できます。

［次へ］をタップして、そのまま［すべての友だち］に送ってみましょう。さてここで［すべての友だち］に送ったら、LINEの友だち全員にこの変なメッセージが届いてしまわないか、ちょっと不安になりますね。

でも大丈夫です。あなたはLINEから、LINE公式アカウントを作りましたが、LINEの友だちと、LINE公式アカウントの友だちは別物なので、LINEの友だち全員にこのメッセージが届いてしまうことはありません。安心して［配信］をタップしましょう。

では自分のLINEに戻って、メッセージが届いたか確認してみます。みんなに届かなくても、少なくともLINE公式アカウントを作った創造主である自分には届いているかな、と思いましたが、残念ながら何も届いていません。なぜならばあなたはまだ、自分で作ったLINE公式アカウントと友だちになっていないからです。かなしい。［メッセージ配信］から［配信済み］を開いて、いま送ったメッセージを確認しても［配信人数］はゼロのままです。なぜならば友だちがいないから！

===[column] 【コラム】個人のLINEアカウントをLINE公式アカウントに切り替えられる？

あなたはおしゃれなタピオカミルクティー屋さんの店員で、TikTokなどでたくさんのフォロワーを抱えるインフルエンサーで、LINEの友だちも3,000人くらいいるとします。@<fn>{tapioca}

TikTokで認証済みアカウントになって認証バッジをもらうような感じで、個人のLINEアカウントを認定してもらってLINE公式アカウントに切り替えられないのかな？と思ったのですが、そんなことは可能なのでしょうか？

結論から言うと、個人のLINEアカウントをLINE公式アカウントに昇格させることはできません。折角個人のLINEアカウントでたくさんの友だちを集めても、それをそのままLINE公式アカウントに引き継ぐことはできないので、仕事や宣伝を目的としてLINEで友だちを増やしたいなら、最初からLINE公式アカウントではじめるのがオススメです。

===[/column]

//footnote[tapioca][普段、Twitterで暮らしているので、おしゃれなインフルエンサーの解像度が低い。]

=== LINE公式アカウントと友だちになる

=== LINE公式アカウントとBotの違い

=== チャットボットとは

チャットボットとは、リアルタイムにメッセージをやりとりする「チャット」と、人間のように動いたり働いたりする機械の「ロボット」を組み合わせた言葉です。チャットボットの裏側には人間がいるわけではなく、プログラムがメッセージの内容に応じた返信をしてくれたり、自動でメッセージを送ってきたりしています。

このチャットボットは、近年では身近な存在になったことで、単に「ボット」と呼ばれることの方が多いかもしれません。Twitterで地震が起きるとすぐに震度を知らせてくれる地震速報ボットや、著名人の名言を定期的につぶやくボット、特定の用語に反応してリプライしてくるボットなどを、あなたも一度は見たことがあるのではないでしょうか。会社のSlackに、GitHubの通知をしてくれるボットやメッセージを自動翻訳してくれるボットがいる、というケースもあるかも知れません。

本書では、この自動応答するチャットボットのプログラムのことを「ボット」と呼びます。

=== プレミアムIDとベーシックID

LINE公式アカウントを作ると、最初に「ベーシックID」というものが自動で割り振られます。@マークと、ランダムな3桁の数字と5桁の英字で構成された「@184ylqsv」みたいなものがベーシックIDです。

LINEの検索窓でこのベーシックIDを検索すると、ちゃんとLINE公式アカウントにたどり着けるのですが、ランダムな文字列をユーザーに「184の…わいえる…きゅー…えすぶい」のように入力させるようにことになるのはなかなか難儀です。もうちょっと名前っぽい、覚えやすいIDがほしくなりますよね。

そこでなんと、お金さえ出せば希望の「プレミアムID」が取得できます！但し、プレミアムIDは一意なので、他の人が既に取得しているプレミアムIDと重複するものは取得できません。

 * @<href>{https://www.linebiz.com/jp/service/line-official-account/plan/}

プレミアムIDを取得しても、ベーシックIDや、過去に作った友だち追加のQRコードは引き続き使用できますので安心してください。

=== 未認証アカウントと認証済アカウント

LINE公式アカウントには認証ステータスというものがあり、未認証アカウントと認証済アカウントの2種類に分けられます。

 * @<href>{https://www.linebiz.com/jp/service/line-official-account/verified-account/}

認証済アカウントになると、青色のバッジがついて「公式っぽさ」が増すと共に、LINE内でアカウント名や概要が検索対象@<fn>{account-name}になり、検索結果に表示されるようになります。@<fn>{search}

//footnote[account-name][未認証アカウントの場合、アカウント名や概要は検索に引っかかりませんが、ベーシックIDやプレミアムIDで検索した場合はしっかり検索結果に表示されます。]
//footnote[search][厳密に言えば、認証済アカウントになると検索結果に表示させるのか、非表示にしておくのかを選べるようになります。たとえば「お金を払って謎解きゲームのチケットを買った人だけ、LINE公式アカウントと友だちになってゲームに参加できる」というようなことを実現したい場合は、検索結果には表示されないよう「非表示」を選んでおきましょう。 @<href>{https://www.linebiz.com/jp/manual/OfficialAccountManager/tutorial-step5/}]

逆に言えば、未認証アカウントであれば、友だち追加のQRコードや、ベーシックIDを自ら流出させない限り、知らない人が勝手に友だち追加される可能性は低いです。

===[column] 【コラム】開発中のLINE公式アカウントをリリース日まで非公開にしておける？

開発中のLINE公式アカウントが人目に触れてしまうことのないよう、リリース日まではアカウントそのものを非公開にしておきたい！と思ったとします。そんなことは可能なのでしょうか？

残念ながらLINE公式アカウントには「非公開」と「公開」、あるいは「開発中」と「リリース済み」というような状態管理がありません。作られた瞬間から、ベーシックIDやプレミアムIDさえ分かれば、リリース前だろうがなんだろうが誰でも友だち追加できてしまいます。

リリース前や開発用のLINE公式アカウントは、うっかりベーシックIDやプレミアムID、そして友だち追加のURLなどを外部に露出させないよう注意しましょう。

また認証済アカウントにした場合は、「検索結果での表示」をデフォルトの「非表示」のままにしておきましょう。

===[/column]

===[column] 【コラム】開発中のLINE公式アカウントに知らない人が友だち追加されてしまった。ブロックできる？

個人的な開発用途としてLINE公式アカウントを作っていたのに、うっかり友だち追加のURLをTwitterに書いてしまい、知らない人に友だち追加されてしまった。まだ開発途中なので、あれこれ見られたくない……LINE公式アカウント側から、友だちをブロックすることはできるのでしょうか？

結論から言うと、LINE公式アカウント側から友だちをブロックしたり、削除したりすることはできません。

===[/column]

===[column] 【コラム】開発チームだけにメッセージのテスト配信がしたい

たとえば本番用のLINE公式アカウントと、テスト環境用のLINE公式アカウントを別々に用意していて、開発チームのAさん、Bさん、Cさんがテスト環境用のLINE公式アカウントと友だちになっていたような場合、Cさんが退職してしまうと、AさんBさん側でCさんをテスト環境用のLINE公式アカウントの友だちからキックするような方法がありません。退職前にCさんに頼んで、テスト環境用のLINE公式アカウントをブロックしてもらうしかないのです。

さらに厳密に言うと、一度対面であって目の前でブロックの操作をしてもらったとしても、ブロックは解除できるので、悪意のあるCさんがブロックを解除してしまうことはとめられません。

なので一度友だち追加されたら、開発者側からは友だち状態はコントロールできないという前提で、色々仕様を組んでおく必要があります。

たとえば、テスト配信はテスト環境用のLINE公式アカウントから送るとしても、ブロードキャストメッセージで全員に送るのではなく、開発チームのAさんBさんCさんのユーザーIDを指定したマルチキャストメッセージを送る、という方法がオススメです。これならCさんの退職後、開発チームに残ったAさんBさんが送信対象からCさんのユーザーIDを消せば、Cさんには公開前のテストメッセージが届かなくなります。

===[/column]

=== プロバイダーとは

=== チャネルとは

=== アカウントの管理方法

==== 複数人で開発するとき

== LINE公式アカウントの運用方法

== LINEキャンパスで資格を取ってみよう

== ツール編

=== LINE Official Account Managerで運用する

=== LINE公式アカウント管理アプリで運用する

=== Messaging APIで運用する

=== 非公式の管理画面で運用する

== 返信方法編

=== 人間が手打ちのチャットで返信する

=== 自動返信で返信する

=== Messaging APIで返信する

== 用意するもの

=== ボットサーバー

=== ボットサーバーがWebhookを受け取れなかったときの再送機能

== メッセージを送る

=== 友だち追加されたときのあいさつメッセージ

=== 友だち全員にメッセージを一斉配信する

===[column] 【コラム】URLを送る前にOGPの見た目を事前に確認したり、キャッシュを消したりしたい

LINEでURLを含むメッセージを送ると、こんなふうにプレビューが表示されます。（@<img>{url-preview}）

//image[url-preview][URLのプレビュー][scale=0.4]{
//}

実際にメッセージを送る前に、このプレビューでどんな画像やテキストが表示されるのか、確認したかったらどうすればいいのでしょう？

実はPagePokerという公式のツールを使うと、対象ページのOGPタグ@<fn>{ogp}を読み込んで、どんなふうにプレビューが表示されるのかを事前に確認できます。@<fn>{card-validator}

 * Pagepoker @<href>{https://poker.line.naver.jp/}

「Clear Cache」にチェックを入れることで、LINEサーバー側のキャッシュも削除できるということなので、ウェブサイト側でOGPの画像を差し替えた後にここでキャッシュを削除すれば、「URLを投げたらうっかり古い画像がプレビューで表示されてしまった」という事態も避けられます。

OGPタグの書き方については、LINE Developersサイトの「トークとLINE VOOM内のURLプレビューはどのようにして生成されますか？」を参考にしてください。

 * @<href>{https://developers.line.biz/ja/faq/#how-are-the-url-previews-generated}

===[/column]

//footnote[ogp][OGPはOpen Graph Protcolの略です。HTMLにメタデータとして「og:image」のようなOGPタグを書いておくことで、TwitterやLINEなどでそのURLを共有したときに、URLそのままではなく対象ページのタイトルや概要、画像などがカードのように表示されます。]
//footnote[card-validator][TwitterのCard Validatorとか、Facebookのシェアデバッガーみたいなものですね。Card Validatorは気づいたらプレビュー確認機能がなくなっていたけれど。 @<href>{https://cards-dev.twitter.com/validator} @<href>{https://developers.facebook.com/tools/debug/}]

=== 特定の属性を指定してメッセージを送る

=== ユーザーIDを指定して特定の人に送る

=== メッセージ送信元のアイコンと表示名を変更する

=== 無料通数を超えたら自動で追加課金されるのか

== メッセージをWebhookで受け取る

=== 画像などのメディアファイルを指定して取得する

== メッセージ以外のイベントをWebhookで受け取る

=== 友だちになったとき

=== ブロックされたとき

=== ユーザーが何かをタップしたとき

== リッチメニュー

LINE公式アカウントと友だちになると、トーク画面の下部にこんなメニューが表示されます。テキストだけでなく、画像でできた贅沢な多彩なメニュー…つまりリッチなメニュー…リッチなメニューなので…リッチメニュー！そう、これがリッチメニューです。わぁ、リッチ！（@<img>{richmenu}）

//image[richmenu][リッチメニュー][scale=0.4]{
//}

このリッチメニューは、一番下の「メニュー」と書いてあるバーをタップすることで閉じたり開いたりできます。このバーのテキストも、デフォルトの「メニュー」から「メニューはこちら」「お問い合わせの入力はこちら」「ほっとするブレイクタイムを」「会員証」「お役立ち情報はこちら」「人気ランキングをチェック！」「こちらもチェック」「荷物の追跡・再配達・集荷受付」といった様々なテキストに変更できます。

リッチメニューの実態は1枚の画像であり、画像内の各領域にそれぞれリンクを設定することで、公式サイトや予約ページ、特定の機能などにユーザーを誘導できます。

== リッチメニュープレイグラウンドでリッチメニューを体験してみる

リッチメニューの様々な機能は、文字で説明するより体験してみるのが一番分かりやすいです。公式で提供されているリッチメニュープレイグラウンドという、「リッチメニューを体験するためのLINE公式アカウント」と友だちになってみましょう。（@<img>{richmenu-playground-qrcode}）

//image[richmenu-playground-qrcode][リッチメニュープレイグラウンドと友だちになる][scale=0.4]{
//}

「リッチメニューを開く」をタップすると、「メッセージアクションを試す」と表示されます。これは「ユーザーがリッチメニューをタップすることで、特定のメッセージをユーザーから自動送信させる」という機能です。早速試してみましょう。

あなたが入力した訳でも送った訳でもないのに、「message sent successfully!」というメッセージがあなたから送信されました。これがメッセージアクションです。メッセージアクションによって、ユーザーからLINE公式アカウントに対してメッセージが送られ、それによってこんなWebhookがボットサーバーに届きましたよ、というのを解説してくれています。

たとえば「再配達の申し込みをしたかったら、LINEで『再配達』というメッセージを送ってね」のように、ユーザーに手入力を促さなくても、リッチメニューに「再配達の申し込み」というボタンを用意して、そのボタンの領域をタップしたら「再配達」というメッセージが自動送信されるよう、対象の領域にメッセージアクションを設定しておけばいいのです。

== リッチメニューの画像を作る

LINE Official Account Managerでリッチメニューの作成画面を開くと、「デザインガイド」というボタンがあり、そこからリッチメニューのテンプレート画像がダウンロードできます。本書ではこのテンプレートをそのまま使ってリッチメニューを設定してみます。

リッチメニューの画像は、LINE Official Account Managerで作成することも可能ですし、Canvaなどで自作しても構いません。サイズの制約は横幅が800px以上2500px以下、高さが250px以上となっています。参考までに3マスが2段重ねで6マス分のテンプレート画像だと横幅が2500px、高さが1686pxで作られていました。

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

== リッチメニューの設定の種類

== 3つの設定方法と表示の優先順位

=== OA Managerで設定したリッチメニュー

=== Messaging APIで設定したリッチメニュー

=== ユーザー単位のリッチメニュー

== どんな見た目のメッセージが送れるのか

=== テキストメッセージ

=== スタンプメッセージ

=== 画像メッセージ

LINE Creative Labを使うと、画像メッセージとして送るような素敵なクリエイティブが簡単に作れます。

 * LINE Creative Lab
 ** @<href>{https://creativelab.line.biz/}

==== 送れるスタンプの種類

==== 自社のスタンプを使う方法

=== Flex Message

== やりとりする場所

=== ユーザーとのトーク

=== グループトーク

=== 複数人トーク

== Messaging API以外のプロダクトとの組み合わせ

=== LINE Social Plugins

==== 自分のサイトに「友だち追加」ボタンを設置してみよう

=== LINE VOOM

=== LINEログイン

=== LIFFやLINEミニアプリ

=== プロバイダーページ

== 開発を始める

== Messaging API SDKを使おう

=== Java

=== PHP

=== Go

=== Perl

=== Ruby

=== Python

=== Node.js

== コミュニティに参加しよう

=== LINE Developers community