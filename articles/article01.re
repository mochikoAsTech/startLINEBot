= LINE公式アカウントをつくってみよう

さっそくLINE公式アカウントを作ってみましょう。

//pagebreak

== LINE公式アカウントとは

服屋さんのレジで「LINEで友だちになると5%オフになるクーポンがもらえるんですが、よかったらどうですか？」と声をかけられたり、カフェでテーブルの上に「友だち追加するとワンドリンク無料！」と書かれたポップが置いてあるのを見たことはありませんか？（@<img>{line-oa-example}）

//image[line-oa-example][街中で見かけるLINE公式アカウント][scale=0.8]{
//}
↑画像の使用NG

普段、あなたはLINEで友だちとメッセージや写真をやりとりしていると思います。実在する人間の友だちとやりとりするのと同じように、LINEでは企業や店舗ともやりとりできます。この企業や店舗のアカウントが「LINE公式アカウント」と呼ばれるものです。

LINE公式アカウントには、企業や店舗だけでなく、芸能人のものも存在します。たとえば地震のときに誰よりも早く「大丈夫？」とメッセージをくれて、彼氏感がすごい、と話題になった芸能人のLINE公式アカウント@<fn>{takeru}もありました。

//footnote[takeru][これは好きになっちゃう…。地震直後に送られた佐藤健のLINEが話題に | BuzzFeed - バズフィードジャパン @<href>{https://www.buzzfeed.com/jp/harunayamazaki/satotakeru-line-0214}]

以前の「LINE@（ラインアット）」という名称の方が見覚えがある、という人も居るかもしれません。LINE@は2019年4月18日にLINE公式アカウントへ統合された@<fn>{lineat}のですが、いまだにLINE@の名前で友だちを募集している店頭ポスターを見ることも少なくありません。

//footnote[lineat][LINE@サービス統合および移行について @<href>{https://d.line-scdn.net/stf/line-lp/migrationinfomation-LINEAT190718.pdf}]

このLINE公式アカウントは、企業や店舗などの法人、あるいは芸能人のような「特別に許可を得た人」だけでなく、誰でも、つまりあなたでも無料ですぐに作ることができます。

==={oaprice} LINE公式アカウントにかかる費用

無料ですぐに作れると言われても、本当にお金がかからないのか気になりますよね。LINE公式アカウントにかかる費用について説明しておきましょう。

LINE公式アカウントには、X年X月時点で3つのプランがあります。それぞれのプランで使える機能に差はなく、無料メッセージの通数や、無料メッセージを使い切ったときに、さらに追加でメッセージが送れるか、という点でのみ違いがあります。

 * コミュニケーションプラン（0円。無料メッセージは200通/月）
 * ライトプラン（月額5,000円。無料メッセージは5,000通/月）
 * スタンダードプラン（月額15,000円。無料メッセージは30,000通/月。さらに追加メッセージは1通3円）

2023年5月31日までは、フリープラン、ライトプラン、スタンダードプランの3種類でしたが、2023年6月1日@<fn>{tbf14}からフリープランの名称がコミュニケーションプランに代わり、それぞれのプランで送れる無料メッセージの通数も変わりました。@<fn>{change-plan}

//footnote[tbf14][本書が出る技術書典14の開催期間（2023年5月20日から2023年6月4日）の途中でちょうどプランが変わるので、ここでは分かりやすく、「今日は2023年6月1日以降だ！」という認知で進みます。2023年5月時点で本書を読んでいるみなさん、いいですか、いまは2023年6月1日以降です。もうプランは変わったのです。]
//footnote[change-plan][【重要：再掲】LINE公式アカウントの月額プラン改定に伴うプラン料金の日割り廃止のお知らせ｜LINE for Business @<href>{https://www.linebiz.com/jp/news/20230125/}]

たとえば友だちが100人いるLINE公式アカウントから、すべての友だちに一斉送信する形でメッセージを2回送ったら、100人×2通でそれだけで200通になりますね。こんなふうにたくさんの友だちにメッセージを継続して送ろうとすると、有料のプランを使う必要がありますが、逆に友だちが自分ひとりだけなら200回送れます。なので本書でちょっと試してみる程度なら無料のコミュニケーションプランで問題ありません。

無料メッセージの通数を使い切れば、次の月初までメッセージが送れなくなるだけで、自分で有料のライトプランやスタンダードプランに申し込まない限りは、メッセージの送りすぎで勝手に課金が始まることはありません。クレジットカードの登録も不要ですので安心してください。

== LINE公式アカウントを作る

LINE公式アカウントについて色々説明しましたが、実際に手を動かしてやってみるのが理解への一番の近道です。LINE公式アカウントを作ってみましょう。

LINE公式アカウントを作る方法には、以下の4つがあります。どれで作っても同じ「LINE公式アカウント」ができます。

 1. LINEで作る
 1. LINE公式アカウント管理アプリで作る
 1. LINE Official Account Managerで作る
 1. LINE Developersコンソールで作る

方法は色々ありますが、注目してほしいのは1番目！そう、なんと専用のアプリや管理画面を使わなくても、作るだけならお手持ちのスマートフォンに入っているLINEで作れるんです！早速、LINEでLINE公式アカウントを作ってみましょう。

==={create-account} LINEでLINE公式アカウントを作ってみる

まずはLINEを開いて、下に並んでいるホーム、トーク、VOOM、ニュース、ウォレットという5つのタブのうち、中央にある［VOOM］をタップしてください。（@<img>{select-voom}）

//image[select-voom][下部の中央にある［VOOM］をタップ][scale=0.8]{
//}
↑広告（他社商材）の掲出のない画像に変更or加工してください

VOOMとやらがなんなのかということはいまは考えずに進みましょう。VOOMタブを開くといきなりショート動画が再生されてびびりますが、右上にある人型のアイコンをタップします。（@<img>{select-icon}）

//image[select-icon][右上にある人型のアイコンをタップ][scale=0.8]{
//}
↑広告（他社商材）の掲出のない画像に変更or加工してください

そして［自分の公式アカウント］の下にある［公式アカウント作成・連携］というボタンをタップします。（@<img>{create-oa}）

//image[create-oa][［公式アカウント作成・連携］をタップ][scale=0.8]{
//}

このとき、もし［公式アカウントを作成するか、既存アカウントを連携するには、メールアドレスを登録してください］と表示されたら、あなたはまだLINEアカウントでメールアドレスを登録していないようです。その場合は、そのまま［登録］をタップします。（@<img>{regist-mail-address}）

//image[regist-mail-address][メールアドレスが未登録だった場合は［登録］をタップ][scale=0.8]{
//}

LINEアカウントに登録するメールアドレスを入力して、［次へ］をタップしてください。ここで登録したメールアドレスは、後でまた必要になります。どのメールアドレスを登録したのか忘れないようにしてください。（@<img>{regist-mail-address-2}）

//image[regist-mail-address-2][メールアドレスを入力して［次へ］をタップ][scale=0.8]{
//}
↑明記する必要性がなければ、メールアドレスは隠したほうが良いかと。

すると入力したメールアドレス宛てに［[LINE] メールアドレス登録確認メール］という件名のメールが届きます。（@<img>{mail-address-check}）

//image[mail-address-check][メールアドレス登録確認メールが届く][scale=0.8]{
//}
↑明記する必要性がなければ、メールアドレスは隠したほうが良いかと。

メールの本文に書いてある4桁の認証番号を、LINEの［メール認証］の画面で入力してください。（@<img>{mail-address-check-2}）

//image[mail-address-check-2][4桁の認証番号をLINEで入力][scale=0.4]{
//}

LINEに［メールアドレスが登録されました。］というメッセージが届いたら、メールアドレスの登録は完了です。（@<img>{mail-address-regist-done}）@<fn>{mail}

//image[mail-address-regist-done][メールアドレスを登録するとメッセージが届く][scale=0.4]{
//}

//footnote[mail][登録したメールアドレスを後で変更したくなったら、下に並んでいる［ホーム］から右上の歯車アイコンをタップして［設定］を開き、［アカウント］の［メールアドレス］で変更できます。]

それでは改めて、VOOMタブの右上にある人型のアイコンから、［公式アカウント作成・連携］というボタンをタップしてください。すると、LINE公式アカウントを紹介する画面が表示されますので、続けて［公式アカウントを作成］をタップします。（@<img>{start-line-oa}）

//image[start-line-oa][［公式アカウントを作成］をタップ][scale=0.4]{
//}

まずはLINE公式アカウントのプロフィール画像とアカウント名を設定します。アカウント名と言われてもピンとこないかもしれませんが、もしあなたが技術書典に出展しているサークルさんなら、サークルの名前とアイコンを設定して、サークルの宣伝をするLINE公式アカウントにしてもいいでしょう。あるいは自分のハンドルネームにしてもいいです。このアカウント名はユニークではないため、既存のLINE公式アカウントとかぶる「テストアカウント」のような名称であっても付けられます。この後、実際にメッセージを送ってみたときにうれしくなるので、何かしら納得のいく名前を付けておくことをお勧めしますが、プロフィール画像もアカウント名も後から変更が可能ですので、悩みすぎずに取りあえずの画像や名前を設定しても構いません。（@<img>{setting-oa-1}）

//image[setting-oa-1][プロフィール画像とアカウント名を設定しよう][scale=0.4]{
//}

カテゴリーは大業種を選ぶと、その下の小業種が選べるようになります。たとえば大業種で［個人］を選ぶと、小業種に［個人（芸術・創造・執筆）］が出てきます。もし自分の本の告知用という位置づけで作るなら、この［個人（芸術・創造・執筆）］という小業種がよさそうですが、他にも［個人（IT・コンピュータ）］や［個人（学生）］、［個人（その他）］などもあるので、個人的に開発を試す用途など、LINE公式アカウントの使い道に応じて適していると思われる業種を選択してください。［会社・事業者の所在国・地域］は、個人の場合は店舗や居住地を選択すればよいので、もしあなたが日本にお住まいなら［日本］を選んでください。（@<img>{setting-oa-2}）

//image[setting-oa-2][使い道に応じて適した大業種と小業種を選ぼう][scale=0.4]{
//}

下部に表示されている［LINE公式アカウント利用規約］と［LINEビジネスID利用規約］はしっかり読んで@<fn>{readtoc}、記載内容に自分が同意できることを確認してから［アカウントを作成］をタップします。

//footnote[readtoc][アカウント名などを全部入力してから利用規約を開いて読み、Androidの戻るボタンで戻ったら、入力した項目が全部消えていた。つらい。]

ここからはいくつか同意の必要なページが出てきます。まず［情報利用に関する同意について］です。こちらもよく読んで、自分が同意できる内容であることを確認してから［同意する］をタップします。（@<img>{consent-of-use}）

//image[consent-of-use][よく読んでから［同意する］をタップ][scale=0.4]{
//}

続いては［ZHDグループへの情報提供に関する個別規約への同意について］です。色んな同意が求められますが、これもきちんと読んでから、同意できる内容であれば［同意する］をタップします。（@<img>{zhd}）

//image[zhd][これもよく読んで［同意する］をタップ][scale=0.4]{
//}

おめでとうございます！これで自分のLINE公式アカウントができました！（@<img>{created-oa}）

//image[created-oa][LINE公式アカウントができた！][scale=0.4]{
//}

［コンテンツを投稿してLINE VOOMをはじめよう！］とあるので、どうやらこれで、いま作ったLINE公式アカウントからLINE VOOMに動画が投稿できるようです。

でもLINE VOOMでの動画投稿よりも、友だちへのメッセージの送信を先に試してみたいですよね。LINE公式アカウントから友だちにトークでメッセージが送りたいときはどうすればいいのでしょう？

== LINE公式アカウントからメッセージを送る

LINE公式アカウントから友だちにメッセージを送る方法は、以下の3つがあります。

 1. LINE公式アカウント管理アプリで送る
 1. LINE Official Account Managerで送る
 1. Messaging APIで送る

自由度は1＜2＜3だと思ってください。1はスマホさえあれば簡単にメッセージが送れますが、細かい設定はできません。
2は、1に比べるともう少し凝ったメッセージが作れますが、やはり細かい部分で自由度が低いです。そして3だと自分でコードを書かなければいけないですが、その分かなり自由にメッセージを作り込めます。初めてのメッセージ送信なので、先ずはいちばんお手軽な1のLINE公式アカウント管理アプリから送ってみましょう。

=== 管理アプリを使ってLINE公式アカウントからメッセージを送ってみる

いま作ったばかりのLINE公式アカウントから友だちにメッセージを送るため、既にLINEを使っているスマートフォンで、LINE公式アカウント管理アプリをインストールします。

 * LINE公式アカウント管理アプリ
 ** Android（Google Play）
 *** https://play.google.com/store/apps/details?id=com.linecorp.lineoa（@<img>{kanri-app-for-android}）
 ** iPhone（App Store）
 *** https://apps.apple.com/jp/app/id1450599059（@<img>{kanri-app-for-ios}）

//image[kanri-app-for-android][Android（Google Play）向けの管理アプリ][scale=0.4]{
//}

//image[kanri-app-for-ios][iPhone（App Store）向けの管理アプリ][scale=0.4]{
//}

インストールしたLINE公式アカウント管理アプリを開いて、［LINEアプリで登録・ログイン］をタップします。（@<img>{lineoa-app}）

//image[lineoa-app][［LINEアプリで登録・ログイン］をタップ][scale=0.4]{
//}

先ほどLINE公式アカウントを作成するときに確認を求められた、［LINEビジネスID利用規約］への同意が再び求められます。問題なければ［ログイン・登録］をタップします。（@<img>{lineoa-app-2}）

//image[lineoa-app-2][［ログイン・登録］をタップ][scale=0.4]{
//}

すると、あなたがLINEで登録しているプロフィール情報をLINE公式アカウントの管理アプリに提供して良いか、という認証画面が表示されます。問題なければ［許可する］をタップします@<fn>{info}。（@<img>{lineoa-app-3}）

//footnote[info][もしここで許可した情報提供を、後で取り消したくなった場合は、LINEの［設定］から［アカウント］を開いて、［連動アプリ］で確認したり、取り消したりできます。 @<href>{https://developers.line.biz/ja/docs/line-login/managing-authorized-apps/}]
//image[lineoa-app-3][［許可する］をタップ][scale=0.4]{
//}

管理アプリへにログインすると、さっき作ったLINE公式アカウントが表示されます。早速、［メッセージを配信する］をタップして、メッセージを送ってみましょう。（@<img>{lineoa-app-4}）

//image[lineoa-app-4][LINE公式アカウントが表示されたら［メッセージを配信する］をタップ][scale=0.4]{
//}
↑執筆者のOA IDが露出していますが、問題ないですか？

［追加］をタップして、先ずは［テキスト］を選び、適当なテキストを入力します。（@<img>{send-message-via-app}）

//image[send-message-via-app][［追加］から［テキスト］を選んでテキストを入力する][scale=0.8]{
//}

さらに［追加］をタップして、今度は［スタンプ］を選び、［スタンプを選択］から適当なスタンプを選びます。（@<img>{send-message-via-app-2}）

//image[send-message-via-app-2][［追加］して適当なスタンプを選択する][scale=0.8]{
//}

これでどんなメッセージが送られるのか、右上の［プレビュー］から確認してみましょう。（@<img>{preview-message}）

//image[preview-message][右上の［プレビュー］をタップ][scale=0.4]{
//}

［トークルーム］では、こんな感じの見た目になるようです。［トークリスト］をタップすると、トークの一覧画面での見え方も確認できます。見え方を確認したら、いったんプレビューは右上の［×］で閉じましょう。（@<img>{preview-message-2}）

//image[preview-message-2][トークルームやトークリストでの見え方が送信前に確認できる][scale=0.8]{
//}

メッセージの見え方を確認して問題なければ、［次へ］をタップします。配信先が［すべての友だち］になっていることを確認し、［配信］をタップしてメッセージを送ってみましょう。［このメッセージはすべての友だちにすぐに配信されます。配信しますか？］という確認が表示されました。さてここで本当に［すべての友だち］に送ったら、LINEの友だち全員にこのちょっと変なメッセージが届いてしまわないか、ちょっと不安になりますね。（@<img>{send-message-via-app-3}）

//image[send-message-via-app-3][［すべての友だち］に［配信］してみよう][scale=0.8]{
//}

でも大丈夫です。あなたはLINEから、LINE公式アカウントを作りましたが、LINEアカウントの友だちと、LINE公式アカウントの友だちは別物なので、LINEで友だちになっている人全員にこのメッセージが届いてしまうことはありません。安心して［配信］をタップしましょう。

では自分のLINEに戻って、メッセージが届いたか確認してみましょう。友だちみんなには届かなくても、少なくともLINE公式アカウントを作った創造主である自分には届いているかな、と思いましたが、残念ながら何も届いていません。メッセージを送信した履歴も残っていません。（@<img>{no-message-received}）

//image[no-message-received][自分にはメッセージは届いていなかった][scale=0.4]{
//}
↑広告（他社商材）の掲出のない画像に変更or加工してください

トークルームに送信したメッセージが残っていないのは、前述のとおりLINEアカウントとLINE公式アカウントが別物だからです。先ほどのメッセージは、LINE公式アカウントから送ったのであって、あなたのLINEアカウントから送った訳ではないので、LINEのトークルームに送信履歴は残っていません。そしてメッセージを受信していないのは、あなたがまだ、自分で作ったLINE公式アカウントと友だちになっていないからです。

管理アプリの［メッセージ配信］から［配信済み］を開いて、いま送ったメッセージを確認しても［配信人数］は0です。なぜならば友だちがひとりもいない@<fn>{friend}から！（@<img>{target-is-0}）

//footnote[friend][LINE公式アカウントに友だちがいない、という話なので、自分がダメージを受ける理由はないんだけど、どうしても「友だちがひとりもいない」という文章を書くと、なんかこう「違うんです違うんです！」と言い訳をしたくなってしまう。多くはないけど友だちはいます、たぶん。]

//image[target-is-0][送ったメッセージの［配信人数］が0になっている][scale=0.8]{
//}
↑執筆者のOA IDが露出していますが、問題ないですか？また、広告バナーが見切れている部分、加工して消してください（著名人肖像が絡むので）

===[column] 【コラム】個人のLINEアカウントをLINE公式アカウントに切り替えられる？

たとえばあなたがおしゃれなタピオカミルクティー屋さんの店員で、TikTokなどでたくさんのフォロワーを抱えるインフルエンサーでもあり、LINEの友だちも3,000人くらいいるとします。@<fn>{tapioca}

折角友だちがいっぱいいるので、TikTokで認証済みアカウントになって認証バッジをもらうような感じで、個人のLINEアカウントを運営に認証してもらってLINE公式アカウントに切り替えられないのかな、と思ったのですが、そんなことは可能なのでしょうか？

結論から言うと、個人のLINEアカウントをLINE公式アカウントに昇格させることはできません。折角個人のLINEアカウントでたくさんの友だちを集めても、それをそのままLINE公式アカウントに引き継ぐことはできないので、仕事や宣伝を目的としてLINEで友だちを増やすなら、最初からLINE公式アカウントではじめるのがお勧めです。

===[/column]

//footnote[tapioca][普段、Twitterで暮らしているので、おしゃれなインフルエンサーの解像度が低い。]

=== LINE公式アカウントと友だちになる

残念ながら友だちがひとりもいない状態でメッセージを配信してしまい、メッセージは誰にも届かなかったようです。LINE公式アカウントからメッセージを送って、ちゃんと「友だち」に届くことを確認するため、まずは自分がLINE公式アカウントと友だちになってみましょう。

LINE公式アカウントの管理アプリで［友だちを増やす］をタップして、［URLを作成］を開きます。［URLをコピー］をタップして、友だち追加用のURLをコピーしましょう。（@<img>{add-friends}）

//image[add-friends][［友だちを増やす］から［URLを作成］を開いて［URLをコピー］する][scale=0.8]{
//}
↑執筆者のOA IDが露出していますが、問題ないですか？また、広告バナーが見切れている部分、加工して消してください（著名人肖像が絡むので）

LINEに戻って、Keepメモという自分専用トークルームみたいなところに友だち追加のURLをペーストします。元気よく「友だち募集中」と表示されました。タップして友だちになってみましょう。（@<img>{add-friends-2}）

//image[add-friends-2][LINEのKeepメモにURLをペーストする][scale=0.8]{
//}
↑広告（他社商材）の掲出のない画像に変更or加工してください

先ほど作ったLINE公式アカウントの友だち追加画面が表示されました。［友だち 0］［フォロワー 1］と書いてあります。このフォロワーというのはLINE VOOMのフォロワーのことで、さっきLINE公式アカウントを作ったときに、自動的に自分で自分をフォローしていたので、この［フォロワー 1］は自分のことです。知らない誰かではありません。

さっそく［追加］のアイコンをタップして、LINE公式アカウントと友だちになってみます。友だちになると、アイコンが［追加］から［トーク］に変わるので、［トーク］をタップしてトークルームを開いてみましょう。（@<img>{add-friends-3}）

//image[add-friends-3][［追加］をタップすると友だち追加されて［トーク］に変わる][scale=0.8]{
//}

設定した覚えもないのに「はじめまして！友だち追加ありがとうございます」という元気なメッセージが届いています。誰だお前、私が作ったLINE公式アカウントだけど誰だ。これはLINE公式アカウントの「あいさつメッセージ@<fn>{greetings}」という機能で、友だち追加されたときに、自動で任意のメッセージを送ることができます。LINE公式アカウントを作ると、デフォルトで「あいさつメッセージ」が設定されているので、この元気なメッセージが届いたという訳です。（@<img>{add-friends-4}）

//footnote[greetings][あいさつメッセージについては、@<hd>{article02|greeting}で後述します。]

//image[add-friends-4][「あいさつメッセージ」が届いた][scale=0.4]{
//}

いまKeepメモに貼ったこの友だち追加用のURLをうっかりTwitterなどに書いてしまうと、誰でもあなたのLINE公式アカウントと友だちになれてしまいます。自分しかメッセージを受け取っていないつもりで色々テストしていたら、実は自分以外の人もひっそり見ていた、ということにならないよう、URLの取り扱いには注意しましょう。

===[column] 【コラム】開発用途のLINE公式アカウントに知らない人が友だち追加されてしまった。ブロックできる？

個人的な開発用途としてLINE公式アカウントを作っていたのに、うっかり友だち追加のURLをTwitterに書いてしまい、知らない人に友だち追加されてしまいました。あくまで開発用途のLINE公式アカウントなので、他人にあれこれ見られたくない……そんなとき、LINE公式アカウント側から友だちをブロックすることはできるのでしょうか？

結論から言うと、LINE公式アカウント側から友だちをブロックしたり、削除したりすることはできません。仮に友だち追加した人を特定して、お願いして目の前でブロックしてもらったとしても、後でこっそりブロック解除されることは止められません。一度友だち追加されてしまったら、もう友だちが自分だけだった元の状態には戻せないと思っておいたほうがいいでしょう。

自分以外とは友だちになっていない状態に戻したいのであれば、友だち追加されてしまったLINE公式アカウントは削除して、新しいLINE公式アカウントを作り直しましょう。LINE公式アカウントは、LINE Official Account Manager、またはLINE公式アカウント管理アプリの［アカウント設定］から、［アカウントを削除］で削除できます@<fn>{delete}。一度削除してしまうと、復活させることはできないので注意してください。

===[/column]

//footnote[delete][アカウントを削除するには？ | LINE for Business @<href>{https://linebiz.force.com/help/s/article/000001102?language=ja}]

=== LINE公式アカウントから友だちにメッセージを送ってみる

再びLINE公式アカウント管理アプリに戻ると、「ターゲットリーチ」が先ほどの0から1に変わっています！（@<img>{target-reach}）

//image[target-reach][ターゲットリーチが0から1になった][scale=0.4]{
//}

ターゲットリーチとは、要は「送信対象となる友だち」の総数のことのようです。友だちできた…ひとりできた…自分だけど…。鏡に向かって「私たち今日からお友だちだね…！」と言っている気分になってきましたが、例え相手が自分自身だろうが友だちは友だちです！メッセージを送ってみましょう。先ほどと同じように［メッセージを配信する］をタップします。

［追加］をタップして、先ずは［テキスト］を選び、適当なテキストを入力します。（@<img>{send-message-via-app-again}）

//image[send-message-via-app-again][［追加］から［テキスト］を選んでテキストを入力する][scale=0.8]{
//}

さらに［追加］をタップして、今度は［スタンプ］を選び、［スタンプを選択］から適当なスタンプを選びます。これでどんなメッセージが送られるのか、右上の［プレビュー］から確認してみましょう。（@<img>{send-message-via-app-again-2}）

//image[send-message-via-app-again-2][［追加］して適当なスタンプを選択する][scale=0.8]{
//}

［トークルーム］では、こんな感じの見た目になるようです。さっきより圧の強いメッセージが準備できました。（@<img>{preview-message-again}）

//image[preview-message-again][トークルームやトークリストでの見え方が送信前に確認できる][scale=0.4]{
//}

［次へ］をタップして、そのまま［すべての友だち］に送ってみましょう。さっきは誰にも届きませんでしたが、いまはたったひとりの友だちに届くはずです。私に届け！私のメッセージ…！祈りを込めて［配信］をタップします。（@<img>{send-message-via-app-again-3}）

//image[send-message-via-app-again-3][［すべての友だち］にメッセージを［配信］する][scale=0.8]{
//}

ピロン！LINEの通知が来ました！圧の強いメッセージが来ました。やったね！これで「LINE公式アカウントから友だちにメッセージを送る」というアチーブメントを達成しました。（@<img>{got-a-message}）

//image[got-a-message][LINE公式アカウントからメッセージが届いた！][scale=0.8]{
//}

==={try-message} LINE公式アカウントにメッセージを送ってみる

LINE公式アカウントに「絶対に新刊買ってね！」と圧をかけられたので、ここで「新刊買います！」と返事をしてあげたいのですが、LINE公式アカウントに返事を送ったらいったいどうなるのでしょうか？物は試しです。メッセージを送ってみましょう。

なんと、またしても設定した覚えのない「申し訳ありませんが、個別のお問い合わせを受け付けておりません」というメッセージが返ってきました。誰だお前！私が作ったLINE公式アカウントで勝手に返事してきて誰なんだ。（@<img>{reply-message}）

//image[reply-message][「応答メッセージ」が届いた][scale=0.4]{
//}

これはLINE公式アカウントの「応答メッセージ@<fn>{reply-message}」という機能で、ユーザーからメッセージが届いたときに、自動で任意の返答を送ることができます。LINE公式アカウントを作ると、デフォルトで「応答メッセージ」が設定されているので、このメッセージが届いたという訳です。

//footnote[reply-message][応答メッセージについては、@<hd>{article02|reply}で後述します。]

===[column] 【コラム】LINE公式アカウントのメッセージはさかのぼって見られる？

LINE公式アカウントと友だちになると、メッセージが届くようになりますが、友だちになる以前のメッセージはさかのぼって見られるのでしょうか？

残念ながらメッセージが届くのは友だちになってからなので、友だちになる以前に送信されていたLINE公式アカウントのメッセージを、TwitterやInstagramのようにさかのぼって見ることはできません。

LINE公式アカウントが友だちにメッセージを送るときに、同内容をLINE VOOMにも投稿していれば、そちらはさかのぼって見られます。

===[/column]

== LINE公式アカウントの基礎知識

無事にLINE公式アカウントからのメッセージ送信もできたので、ここでちょっとLINE公式アカウントについていくつか説明をしておきましょう。実践の後の座学タイムです。

=== LINE公式アカウントと普通のLINEアカウントとの違い

先ほどLINEアカウントとLINE公式アカウントは別物という話をしましたが、普通のLINEアカウントとLINE公式アカウントはどうやって見分けがつくのでしょうか？LINE公式アカウントを運用している本人にはもちろん分かりますが、どちらもQRコードを読み込んで友だち追加できるので、友だちになる側はどこで「あ、これLINE公式アカウントだ」と気づけるのでしょう？

友だち追加の画面を比較してみましょう。左がLINE公式アカウントで、右が普通のLINEアカウントです。（@<img>{line-official-account-and-line-account}）

//image[line-official-account-and-line-account][左がLINE公式アカウントで、右が普通のLINE公式アカウント][scale=0.8]{
//}
↑執筆者のOA IDが露出していますが、問題ないですか？

LINE公式アカウントには追加、投稿のボタンが並んでいますが、普通のLINEアカウントだと追加、ブロック、通報のボタンが並んでいます。またLINE公式アカウントの方は、ベーシックID@<fn>{basic}が表示されていたり、［ほかの公式アカウントを見る］や［友だち限定の情報をゲット］とあるので、よく見れば「これ、LINE公式アカウントだな？」と気づけそうです。

//footnote[basic][ベーシックIDについては、@<hd>{article01|premium-and-basic}で後述します。]

トークルームの画面も比較してみましょう。LINE公式アカウントは名前の左に「未認証@<fn>{not-verified}のLINE公式アカウント」であることを示す灰色のバッジが付いています。（@<img>{line-official-account-and-line-account-2}）

//footnote[not-verified][未認証アカウントについては、@<hd>{article01|badge}で後述します。]

//image[line-official-account-and-line-account-2][LINE公式アカウントは名前の左に灰色のバッジが付いている][scale=0.8]{
//}

==={premium-and-basic} プレミアムIDとベーシックID

LINE公式アカウントを作ると、最初に「ベーシックID」というものが自動で割り振られます。@マークと、ランダムな3桁の数字と5桁の英字で構成された「@184ylqsv」みたいなものがベーシックIDです。

LINEの検索窓でこのベーシックIDを検索すると、ちゃんとLINE公式アカウントにたどり着けるのですが、友だち登録してもらうためにランダムな文字列をユーザーに「184の…わいえる…きゅー…えすぶい」のように入力させるのはなかなか難儀です。もうちょっと名前っぽい、覚えやすいIDがほしくなりますよね。

そこでなんと、月額100円（税別）を出せば、4文字から18文字で希望の「プレミアムID@<fn>{premium}」というものが取得できます！但し、プレミアムIDは一意なので、他の人が既に取得しているプレミアムIDと重複するものは取得できません。

//footnote[premium][プレミアムIDとは｜LINE for Business @<href>{https://www.linebiz.com/jp/service/line-official-account/plan/}]

プレミアムIDと有料プランは別枠なので、無料のコミュニケーションプランのまま、プレミアムIDだけ購入することも可能です。またプレミアムIDを取得しても、ベーシックIDや、過去に作った友だち追加のQRコードは引き続き使用できます。

==={badge} 未認証アカウントと認証済アカウント

無料プランと有料プラン、ベーシックIDとプレミアムIDについては既に説明しましたが、実はさらに認証ステータスというものがあり、LINE公式アカウントは未認証アカウントと認証済アカウント@<fn>{verified}の2種類に分けられます。

//footnote[verified][「認証済アカウント」とは？｜メリット・申請方法｜LINE for Business @<href>{https://www.linebiz.com/jp/service/line-official-account/verified-account/}]

認証済アカウントになるためには申請をして、審査に通過する必要がありますが、この申請と審査は無料です。有料プランやプレミアムIDと違って、認証済アカウントになるために費用はかかりません。

では認証済アカウントになると何がうれしいのでしょう？

認証済アカウントになると、バッジの色が灰色から青色になってついて「公式っぽさ」が増すと共に、LINE内でアカウント名や概要が検索対象@<fn>{account-name}になり、検索結果に表示されるようになります。@<fn>{search}逆に言えば、デフォルトの未認証アカウントであれば、友だち追加のQRコードや、ベーシックID、あるいはプレミアムIDを自ら露出しない限り、知らない人が勝手に友だち追加される可能性は低いということです。

//footnote[account-name][未認証アカウントの場合、アカウント名や概要は検索に引っかかりませんが、ベーシックIDやプレミアムIDで検索した場合はしっかり検索結果に表示されます。]
//footnote[search][厳密に言えば、認証済アカウントになると検索結果に表示させるのか、非表示にしておくのかを選べるようになります。たとえば「お金を払って謎解きゲームのチケットを買った人だけ、LINE公式アカウントと友だちになって、LINEのトークからゲームに参加できる」というようなことを実現したい場合は、検索結果には表示されないよう「非表示」を選んでおきましょう。 @<href>{https://www.linebiz.com/jp/manual/OfficialAccountManager/tutorial-step5/}]

また認証済アカウントになると、「友だち募集中」と書かれたキャラクターとQRコード付きのステッカー、三角POPなどが購入できます。お店の入り口に貼ったり、テーブルに置いたりして、友だち追加を促すためのおしゃれな販促物を、わざわざ自分で作らなくても簡単に購入できるのがいいところですね。

ただし認証済アカウントの審査は、個人名では通らない@<fn>{verified-check}ようです。販促物が購入できる、という特典を見ても、認証済アカウントはインフルエンサーなどの個人@<fn>{influencer}ではなく、店舗やサービスなどをターゲットとしているようです。

//footnote[verified-check][LINE公式アカウントの審査とは｜認証済アカウント申請時の注意点 @<href>{https://www.linebiz.com/jp/column/technique/20190829/}]
//footnote[influencer][ちなみに2022年6月には「LINEクリエイターアカウント」という、インフルエンサーやクリエイター向けのLINE公式アカウントの新カテゴリーも発表されていました。 @<href>{https://linecorp.com/ja/pr/news/ja/2022/4265}]

===[column] 【コラム】準備中のLINE公式アカウントをリリース日まで非公開にしておける？

準備中のLINE公式アカウントが人目に触れてしまうことのないよう、リリース日まではアカウントそのものを非公開にしておきたい！と思ったとします。そんなことは可能なのでしょうか？

残念ながらLINE公式アカウントには「非公開」と「公開」、あるいは「開発中」と「リリース済み」というような状態管理がありません。作られた瞬間から、ベーシックIDやプレミアムIDさえ分かれば、リリース前だろうがなんだろうが誰でも友だち追加できてしまいます。

リリース前や準備用のLINE公式アカウントは、うっかりベーシックIDやプレミアムID、そして友だち追加のURLなどを外部に露出させないよう注意しましょう。また認証済アカウントにした場合は、「検索結果での表示」をデフォルトの「非表示」のままにしておきましょう。

===[/column]
