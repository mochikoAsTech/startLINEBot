= LINE公式アカウントをつくってみよう

あなたにも、私にも。LINE公式アカウントは誰にでもつくれる！

//pagebreak

== LINE Botをつくる前に

「LINE Botをつくってみよう」という本なのに、本編を読みはじめたらいきなり@<chap>{article01}で「@<title>{article01}」と書いてあると戸惑いますよね。

実は、話しかけて自動応答するLINE Botを作るには、話しかける相手として「LINE公式アカウント」というものを用意する必要があります。そのため@<chap>{article01}では、このLINE公式アカウントの作り方や、LINE公式アカウントに関する最低限の知識を説明していきます。

でも晩ごはんは肉じゃがにしようと思い立って「肉じゃがをつくろう」という本を開いたのに、前半が「じゃがいもの選び方」「スーパーマーケットと八百屋のどっちで買うべき？」「肉じゃがに適した雪平鍋を用意しよう」などで埋まっていてなかなかレシピが出てこないと、「そういうのいいから！早く！肉じゃがのレシピ！！」と感じると思います。お気持ちは分かります。ただ自動応答するLINE Botをつくるにあたって、先にLINE公式アカウントを用意すると共に、LINE公式アカウントの「中の人」として手動の運用をざっくり体験しておいてもらうことで、自動応答のLINE Botをつくったときに「あー、さっき手でやったあの作業をコードのこの部分でやらせてるんだ！」が分かりやすくなるので、敢えてこういった構成にしています。

@<chap>{article01}を読んでから@<chap>{article02}、という順番で読み進めてもらうのがお勧めではありますが、「細かいことはいいから！早くLINE Botを作らせて！」という方は、@<hd>{article01|create-account}だけやったら、あとは読み飛ばして@<chapref>{article02}に進んでも構いません。

それでは今度こそ、はじまりはじまりー！@<fn>{otaku}

//footnote[otaku][本書はLINE公式アカウントやLINE BotやMessaging APIについて、筆者が書きたいこと伝えたいとことをぎゅうぎゅうに詰め込んで作った本です。「なんでこの話、いまここでするんだろう？」と感じたら、そのときは「たぶん…ただ書きたかったんだな…」と思って、情報量の調整にしくじったヲタクの早口を聞くつもりで温かく見守ってください。よろしくお願いします。]

//pagebreak

== LINE公式アカウントとは

服屋さんのレジで「LINEで友だちになると5%オフになるクーポンがもらえるんですが、よかったらどうですか？」と声をかけられたり、カフェでテーブルの上に「友だち追加するとワンドリンク無料！」と書かれたポップが置いてあったりするのを見たことはありませんか？（@<img>{line-oa-example}）

//image[line-oa-example][街中で見かけるLINE公式アカウント][scale=1]{
//}

普段、あなたはLINEで友だちとメッセージや写真をやりとりしていると思います。実在する人間の友だちとやりとりするのと同じように、LINEでは企業や店舗ともやりとりできます。この企業や店舗のアカウントが「LINE公式アカウント」@<fn>{line-at}と呼ばれるものです。

LINE公式アカウントには、企業や店舗だけでなく、芸能人のものも存在します。たとえば地震のときに誰よりも早く「大丈夫？」とメッセージをくれて、彼氏感がすごい、と話題になった芸能人のLINE公式アカウント@<fn>{takeru}もありました。

//footnote[line-at][以前の「LINE@（ラインアット）」という名称の方が見覚えがある、という人も居るかもしれません。LINE@は2019年4月18日にLINE公式アカウントへ統合されたのですが、いまだにLINE@の名前で友だちを募集している店頭ポスターを見ることも少なくありません。 @<href>{https://d.line-scdn.net/stf/line-lp/migrationinfomation-LINEAT190718.pdf}]
//footnote[takeru][これは好きになっちゃう…。地震直後に送られた佐藤健のLINEが話題に | BuzzFeed - バズフィードジャパン @<href>{https://www.buzzfeed.com/jp/harunayamazaki/satotakeru-line-0214}]

このLINE公式アカウントは、企業や店舗などの法人、あるいは芸能人のような「特別に許可を得た人」だけでなく、誰でも、つまりあなたでも無料ですぐに作ることができます。

==={oaprice} LINE公式アカウントにかかる費用

無料ですぐに作れると言われても、本当にお金がかからないのか気になりますよね。LINE公式アカウントにかかる費用について説明しておきましょう。

LINE公式アカウントには、2023年6月時点で3つのプランがあります。それぞれのプランで使える機能に差はなく、無料メッセージの通数や、無料メッセージを使い切ったときに、さらに追加でメッセージが送れるか、という点でのみ違いがあります。（@<img>{list-of-plans}）

//image[list-of-plans][2023年6月時点のLINE公式アカウントの料金プラン][scale=1]{
//}

2023年5月31日までは、フリープラン、ライトプラン、スタンダードプランの3種類でしたが、2023年6月1日@<fn>{tbf14}からフリープランの名称がコミュニケーションプランに代わり、それぞれのプランで送れる無料メッセージの通数も変わりました。@<fn>{change-plan}

//footnote[tbf14][本書が出る技術書典14の開催期間（2023年5月20日から2023年6月4日）の途中でちょうどプランが変わるので、ここでは分かりやすく、「今日は2023年6月1日以降だ！」という認知で進みます。2023年5月時点で本書を読んでいるみなさん、いいですか、いまは2023年6月1日以降です。もうプランは変わったのです。]
//footnote[change-plan][【重要：再掲】LINE公式アカウントの月額プラン改定に伴うプラン料金の日割り廃止のお知らせ｜LINE for Business @<href>{https://www.linebiz.com/jp/news/20230125/}]

たとえば友だちが100人いるLINE公式アカウントから、すべての友だちに一斉送信する形でメッセージを2回送ったら、100人×2通でそれだけで200通になりますね。こんなふうにたくさんの友だちにメッセージを継続して送ろうとすると、有料のプランを使う必要がありますが、逆に友だちが自分ひとりだけなら200回送れます。なので本書でちょっと試してみる程度なら無料のコミュニケーションプランで問題ありません。

無料メッセージの通数を使い切れば、次の月初までメッセージが送れなくなるだけで、自分で有料のライトプランやスタンダードプランに申し込まない限りは、メッセージの送りすぎで勝手に課金が始まることはありません。クレジットカードの登録も不要ですので安心してください。

== LINE公式アカウントを作る

LINE公式アカウントについて色々説明しましたが、実際に手を動かしてやってみるのが理解への一番の近道です。あなたもLINE公式アカウントを作ってみましょう。

LINE公式アカウントを作る方法には、次の4つがあります。どれで作っても同じ「LINE公式アカウント」ができます。

 1. LINEで作る
 1. LINE公式アカウント管理アプリ@<fn>{kanri-app-link}で作る
 1. LINE Official Account Manager@<fn>{oamanager-url}で作る
 1. LINE Developersコンソール@<fn>{console-url}で作る

方法は色々ありますが、注目してほしいのは1番目！そう、なんと専用のアプリや管理画面を使わなくても、作るだけならお手持ちのスマートフォンに入っているLINEで作れるんです！早速、LINEでLINE公式アカウントを作ってみましょう。

//footnote[kanri-app-link][LINE公式アカウント管理アプリについては、@<hd>{article01|kanri-app}で後述します。]
//footnote[oamanager-url][LINE Official Account Managerについては、@<hd>{article02|login-oamanager}で後述します。]
//footnote[console-url][LINE Developersコンソールについては、@<hd>{article02|issue-token}で後述します。]

==={create-account} LINEでLINE公式アカウントを作ってみる

先ずはLINEを開いて、下に並んでいるホーム、トーク、VOOM、ニュース、ウォレットという5つのタブのうち、中央にある［VOOM］タブをタップしてください。（@<img>{select-voom-1}）

VOOMとやらがなんなのかということは、ひとまず考えずに進みましょう。VOOMタブを開くといきなりショート動画が再生されてびびりますが、［フォロー中］を開いた後、右上にある人型のアイコンをタップします。

そして［自分の公式アカウント］の下にある［公式アカウント作成・連携］というボタンをタップしてください。@<fn>{programming}

//image[select-voom-1][［VOOM］タブを開いて［公式アカウント作成・連携］をタップ][scale=1]{
//}

//footnote[programming][「はじめに」で「プログラム書いて動かしてみようぜ！」と元気よく誘ってはじまった割に、ここからしばらくスマートフォンの画面でぽちぽちする作業が続きます。「俺は開発をしに来たのになんでここで焼きそばを作らされているんだ…」みたいな気持ちになるかもしれませんが、第1章でぬくもりを感じる手作業でのメッセージ配信を体験しておくことで、第2章でチャットボットに何をさせているのかが理解しやすくなるはずです。第1章の間は前向きな気持ちで焼きそば、もといスマートフォンでの画面操作をお楽しみください。]

このとき、もし［公式アカウントを作成するか、既存アカウントを連携するには、メールアドレスを登録してください］と表示されたら、あなたはまだLINEアカウントでメールアドレスを登録していないようです。その場合は、そのまま［登録］をタップします。（@<img>{regist-mail-address-1}）

LINEアカウントに登録するメールアドレスを入力したら、［次へ］をタップしてください。ここで登録したメールアドレスは、後でまた必要になります。どのメールアドレスを登録したのか忘れないようにしてください。

//image[regist-mail-address-1][未登録だった場合はメールアドレスを入力して［次へ］をタップ][scale=0.8]{
//}

//pagebreak

入力したメールアドレス宛てに［[LINE] メールアドレス登録確認メール］という件名のメールが届きます。（@<img>{mail-address-check-1}）

メールの本文に書いてある4桁の認証番号を、LINEの［メール認証］の画面で入力してください。

//image[mail-address-check-1][メールアドレス登録確認メールが届いたら認証番号をLINEで入力][scale=1]{
//}

//pagebreak

LINEに［メールアドレスが登録されました。］というメッセージが届いたら、メールアドレスの登録@<fn>{mail}は完了です。それでは改めて［VOOM］タブを開いて、右上にある人型のアイコンから、［公式アカウント作成・連携］というボタンをタップしてください。（@<img>{mail-to-voom}）

//image[mail-to-voom][LINEにメッセージが届いたら再び［公式アカウント作成・連携］をタップ][scale=1]{
//}

//footnote[mail][登録したメールアドレスを後で変更したくなったら、下に並んでいる［ホーム］タブから右上の歯車アイコンをタップして［設定］を開き、［アカウント］の［メールアドレス］で変更できます。]

//pagebreak

LINE公式アカウントを紹介する画面が表示されたら、［公式アカウントを作成］をタップしてください。先ずはLINE公式アカウントのプロフィール画像とアカウント名を設定します。アカウント名と言われてもピンとこないかもしれませんが、もしあなたが技術書典に出展しているなら、サークルの名前とアイコンを設定してサークルの宣伝をするLINE公式アカウントにしてもいいでしょう。あるいは自分のハンドルネームにしてもいいと思います。このアカウント名はユニークではないため、既存のLINE公式アカウントとかぶる「テストアカウント」のような名称であっても付けられます。@<fn>{name}（@<img>{start-line-oa-1}）

//image[start-line-oa-1][［公式アカウントを作成］からプロフィール画像とアカウント名を設定][scale=0.8]{
//}

//footnote[name][この後、実際にメッセージを送ってみたときにうれしくなるので、何かしら愛着の持てる名前を付けておくことをお勧めしますが、プロフィール画像もアカウント名も後から変更が可能ですので、悩みすぎずに取りあえずの画像や名前を設定しても構いません。]

カテゴリーは大業種を選ぶと、その下の小業種が選べるようになります。たとえば大業種で［個人］を選ぶと、小業種に［個人（芸術・創造・執筆）］が出てきます。もし自分の本の告知用という位置づけで作るなら、この［個人（芸術・創造・執筆）］という小業種がよさそうですが、他にも［個人（IT・コンピュータ）］や［個人（学生）］、［個人（その他）］などもあるので、個人的に開発を試す用途など、LINE公式アカウントの使い道に応じて適していると思われる業種を選択してください。［会社・事業者の所在国・地域］は、個人の場合は店舗や居住地を選択すればよいので、もしあなたが日本にお住まいなら［日本］を選んでください。（@<img>{setting-oa}）

下部に表示されている［LINE公式アカウント利用規約］と［LINEビジネスID利用規約］も確認したら@<fn>{readtoc}、［アカウントを作成］をタップします。［情報利用に関する同意について］と［ZHDグループへの情報提供に関する個別規約への同意について］もそれぞれ確認し、同意できる内容であれば［同意する］をタップしてください。

//image[setting-oa][大業種と小業種、所在国を選んだら［アカウントを作成］をタップ][scale=1]{
//}

//footnote[readtoc][アカウント名などを全部入力してから利用規約を開いて読み、Androidの戻るボタンで戻ったら、入力した項目が全部消えていた。つらい。]

おめでとうございます！これで自分のLINE公式アカウントができました！@<fn>{skip}（@<img>{created-oa}）

//footnote[skip][「細かいことはいいから！早くLINE Botを作らせて！」という方は、第1章の残りはスキップして@<chapref>{article02}に進んでも構いません。]

//image[created-oa][LINE公式アカウントができた！][scale=0.4]{
//}

［コンテンツを投稿してLINE VOOMをはじめよう！］とあるので、どうやらこれで、いま作ったLINE公式アカウントからLINE VOOMに動画が投稿できるようです。

でも、もともとショート動画が投稿したかった訳ではないので、それよりも友だちへのメッセージの送信を試してみたいですよね。LINE公式アカウントから友だちにトークでメッセージが送りたいときはどうすればいいのでしょう？

== LINE公式アカウントからメッセージを送る

LINE公式アカウントから友だちにメッセージを送る方法には、次の3つ@<fn>{cannot}があります。

//footnote[cannot][LINEでは、LINE公式アカウントを作ることはできても、LINE公式アカウントからメッセージを送るところまではできません。]

 1. LINE公式アカウント管理アプリで送る
 1. LINE Official Account Managerで送る
 1. Messaging APIで送る

1と2はどちらもLINE公式アカウントを運用していくための管理画面で、1がスマートフォンのアプリ、2がウェブサイトです。3については@<chapref>{article02}で詳しく説明しますので、ここでは「なるほど、Messaging APIというものがあるのか」と軽く流してしまって構いません。

LINE公式アカウントから友だちにメッセージを送る方法はこの3つですが、これらの大きな違いは自由度です。自由度は1＜2＜3の順で高くなっていくと思ってください。1はスマートフォンさえあれば簡単にメッセージが送れますが、細かい設定はできません。2は、1に比べるともう少し凝ったメッセージが作れますが、やはり細かい部分で自由度に限りがあります。そして3だと自分でコードを書かなければいけないですが、その分かなり自由にメッセージを作り込めます。

初めてのメッセージ送信なので、先ずはいちばんお手軽な1のLINE公式アカウント管理アプリから送ってみましょう。

//pagebreak

==={kanri-app} 管理アプリを使ってLINE公式アカウントからメッセージを送ってみる

いま作ったばかりのLINE公式アカウントから友だちにメッセージを送るため、LINEを使っているスマートフォンに、LINE公式アカウント管理アプリ@<fn>{kanri-app-url}をインストールします。

//image[kanri-apps][LINE公式アカウント管理アプリをインストールしよう][scale=1]{
//}

//footnote[kanri-app-url][Androidなら@<href>{https://play.google.com/store/apps/details?id=com.linecorp.lineoa}、iPhoneなら@<href>{https://apps.apple.com/jp/app/id1450599059}からインストールできます。]

//pagebreak

インストールできたらLINE公式アカウント管理アプリを開いてください。（@<img>{icon}）

//image[icon][LINE公式アカウント管理アプリを開く][scale=0.3]{
//}

［LINEアプリで登録・ログイン］をタップします。（@<img>{lineoa-app-1}）

先ほどLINE公式アカウントを作成するときに確認を求められた、［LINEビジネスID利用規約］への同意が再び求められますので、［ログイン・登録］をタップしてください。

//image[lineoa-app-1][［LINEアプリで登録・ログイン］と［ログイン・登録］をタップ][scale=0.8]{
//}

//pagebreak

すると、あなたがLINEで登録しているプロフィール情報をLINE公式アカウントの管理アプリに提供して良いか、という認証画面が表示されます。問題なければ［許可する］をタップしてください@<fn>{info}。（@<img>{lineoa-app-2}）

管理アプリへにログインすると、さっき作ったLINE公式アカウントが表示されます。早速、［メッセージを配信する］をタップして、メッセージを送ってみましょう。

//footnote[info][もしここで許可した情報提供を、後で取り消したくなった場合は、LINEの［設定］から［アカウント］を開いて、［連動アプリ］で確認したり、取り消したりできます。 @<href>{https://developers.line.biz/ja/docs/line-login/managing-authorized-apps/}]

//image[lineoa-app-2][［許可する］でLINE公式アカウントが表示されたら［メッセージを配信する］][scale=0.8]{
//}

［追加］をタップして［テキスト］を選び、適当なテキストを入力します。（@<img>{send-message-via-app}）

//image[send-message-via-app][［追加］から［テキスト］を選んでテキストを入力する][scale=0.8]{
//}

これでどんなメッセージが送られるのか、右上の［プレビュー］から確認してみましょう。（@<img>{preview-message-1}）

//image[preview-message-1][右上の［プレビュー］からトークルームやトークリストでの見え方を確認しよう][scale=0.8]{
//}

［トークルーム］では、こんな感じの見た目になるようです。［トークリスト］をタップすると、トークの一覧画面での見え方も確認できます。見え方を確認したら、プレビューは右上の［×］で閉じて［次へ］をタップします。

配信先が［すべての友だち］になっていることを確認し、［配信］をタップしてメッセージを送ってみましょう。［このメッセージはすべての友だちにすぐに配信されます。配信しますか？］という確認が表示されました。さてここで本当に［すべての友だち］に送ったら、LINEの友だち全員に新刊の購入を迫る変なメッセージが届いてしまわないか、ちょっと不安になりますね。（@<img>{send-message-via-app-3}）

//image[send-message-via-app-3][［すべての友だち］に［配信］してみよう][scale=1]{
//}

でも大丈夫です。あなたはLINEから、LINE公式アカウントを作りましたが、LINEアカウントの友だちと、LINE公式アカウントの友だちは別物なので、LINEで友だちになっている人全員にこのメッセージが届いてしまうことはありません。安心して［配信］をタップしましょう。

//pagebreak

では自分のLINEに戻って、メッセージが届いたか確認してみましょう。友だちみんなには届かなくても、少なくともこのLINE公式アカウントの創造主である自分にはメッセージが届いているかな、と思いましたが、残念ながら何も届いていません。メッセージを送信した履歴も残っていません。（@<img>{no-message-received}）

//image[no-message-received][自分にもメッセージは届いていなかった][scale=0.4]{
//}

トークルームに送信したメッセージが残っていないのは、前述のとおりLINEアカウントとLINE公式アカウントが別物だからです。先ほどのメッセージは、LINE公式アカウントから送ったのであって、あなたのLINEアカウントから送った訳ではないので、LINEのトークルームに送信履歴は残っていません。そしてメッセージを受信していないのは、あなたがまだ、自分で作ったLINE公式アカウントと友だちになっていないからです。

管理アプリの［メッセージ配信］から［配信済み］を開いて、いま送ったメッセージを確認しても［配信人数］は0です。なぜならば友だちがひとりもいない@<fn>{friend}から！（@<img>{target-is-0}）

//footnote[friend][LINE公式アカウントに友だちがいない、という話なので、自分がダメージを受ける理由はないんだけど、どうしても「友だちがひとりもいない」という響きが暴力的で、なんかこう「違うんです違うんです！」と言い訳をしたくなってしまう。ちなみに@<img>{no-message-received}のトークリストにも友だちはいませんが、これは本書の検証用に使っているサブのスマートフォンのLINEアカウントだからです。いるよ！！友だち！！！]

//image[target-is-0][送ったメッセージの［配信人数］が0になっている][scale=1]{
//}

//pagebreak

===[column] 【コラム】個人のLINEアカウントをLINE公式アカウントに切り替えられる？

たとえばあなたがおしゃれなタピオカミルクティー屋さんの店員で、TikTokなどでたくさんのフォロワーを抱えるインフルエンサーでもあり、LINEの友だちも3,000人くらいいるとします。@<fn>{tapioca}

折角友だちがいっぱいいるので、TikTokで認証済みアカウントになって認証バッジをもらうような感じで、個人のLINEアカウントを運営に認証してもらってLINE公式アカウントに切り替えられないのかな、と思ったのですが、そんなことは可能なのでしょうか？

結論から言うと、個人のLINEアカウントをLINE公式アカウントに昇格させることはできません。折角個人のLINEアカウントでたくさんの友だちを集めても、それをそのままLINE公式アカウントに引き継ぐことはできないので、仕事や宣伝を目的としてLINEで友だちを増やすなら、最初からLINE公式アカウントではじめるのがお勧めです。

===[/column]

//footnote[tapioca][普段、Twitterで暮らしているので、おしゃれなインフルエンサーの解像度が低い。]

//pagebreak

=== LINE公式アカウントと友だちになる

残念ながら友だちがひとりもいない状態でメッセージを配信してしまったため、折角送ったメッセージですが誰にも届かなかったようです。LINE公式アカウントからメッセージを送って、ちゃんと「友だち」に届くことを確認するため、先ずは自分がLINE公式アカウントと友だちになってみましょう。

LINE公式アカウントの管理アプリで［友だちを増やす］をタップして、［URLを作成］を開きます。［URLをコピー］をタップして、友だち追加用のURL@<fn>{friend-url}をコピーしましょう。（@<img>{add-friends}）

//footnote[friend-url][ちなみに本書で筆者が作ったこのLINE公式アカウントとは実際に友だちになれます。LINEで筆者と友だちになってみよう。 @<href>{https://lin.ee/QpolyfU}]

//image[add-friends][［友だちを増やす］から［URLを作成］を開いて［URLをコピー］する][scale=1]{
//}

//pagebreak

LINEに戻って、Keepメモという自分専用トークルームみたいなところに友だち追加のURLをペーストします。元気よく「友だち募集中」と表示されました。タップして友だちになってみましょう。（@<img>{add-friends-2}）

//image[add-friends-2][LINEのKeepメモにURLをペーストする][scale=1]{
//}

この友だち追加用のURLをうっかりTwitterなどに書いてしまうと、誰でもあなたのLINE公式アカウントと友だちになれてしまいます。自分しかメッセージを受け取っていないつもりで色々テストしていたら、実は自分以外の人もひっそり見ていた、ということにならないよう、友だち追加のURLの取り扱いには注意しましょう。

//pagebreak

URLを開くと、先ほど作ったLINE公式アカウントの友だち追加画面@<fn>{follower}が表示されました。さっそく［追加］のアイコンをタップして、LINE公式アカウントと友だちになってみます。友だちになると、アイコンが［追加］から［トーク］に変わるので、［トーク］をタップしてトークルームを開いてみましょう。（@<img>{add-friends-got-greeting}）

//footnote[follower][［友だち 0］［フォロワー 1］とありますが、このフォロワーというのはLINE VOOMでLINE公式アカウントをフォローしている人のことです。さっきLINE公式アカウントを作ったときに、自動的に自分で自分をフォローしていたので、この［フォロワー 1］は自分自身です。知らない誰かではありません。]

設定した覚えもないのに「はじめまして！mochikoAsTechです。友だち追加ありがとうございます」という元気なメッセージが届いています。誰だお前、私が作ったLINE公式アカウントだけど誰だ。これはLINE公式アカウントの「あいさつメッセージ@<fn>{greetings}」という機能で、友だち追加されたときに、自動で任意のメッセージを送ることができます。LINE公式アカウントを作ると、デフォルトで「あいさつメッセージ」が設定されているので、この元気なメッセージが届いたという訳です。

//image[add-friends-got-greeting][［追加］をタップすると友だち追加されて［トーク］に変わる][scale=1]{
//}

//footnote[greetings][あいさつメッセージについては、@<hd>{article02|greeting}でも後述します。]

===[column] 【コラム】開発用途のLINE公式アカウントが知らない人に友だち追加されてしまった。ブロックできる？

個人的な開発用途としてLINE公式アカウントを作っていたのに、うっかり友だち追加のURLをTwitterに書いてしまい、知らない人に友だち追加されてしまいました。あくまで開発用途のLINE公式アカウントなので、他人にあれこれ見られたくない…そんなとき、LINE公式アカウント側から友だちをブロックすることはできるのでしょうか？

結論から言うと、LINE公式アカウント側から友だちをブロックしたり、削除したりすることはできません。仮に友だち追加した人を特定して、お願いして目の前でブロックしてもらったとしても、後でこっそりブロック解除されることは止められません。一度友だち追加されてしまったら、もう友だちが自分だけだった元の状態には戻せないと思っておいたほうがいいでしょう。

自分以外とは誰とも友だちになっていない状態に戻したいのであれば、友だち追加されてしまったLINE公式アカウントは削除して、新しいLINE公式アカウントを作り直しましょう。LINE公式アカウントは、LINE Official Account Manager、またはLINE公式アカウント管理アプリの［アカウント設定］から、［アカウントを削除］で削除できます@<fn>{delete}。LINE公式アカウントは、一度削除してしまうと復活させることはできないので注意してください。

===[/column]

//footnote[delete][アカウントを削除するには？ | LINE for Business @<href>{https://linebiz.force.com/help/s/article/000001102?language=ja}]

//pagebreak

=== LINE公式アカウントから友だちにメッセージを送ってみる

再びLINE公式アカウント管理アプリに戻ると、「ターゲットリーチ」が先ほどの0から1に変わっています！（@<img>{target-reach}）

//image[target-reach][ターゲットリーチが0から1になった][scale=0.4]{
//}

ターゲットリーチとは、要は「送信対象となる友だち」の総数です。友だちできた…ひとりできた…自分だけど…。鏡に向かって「私たち今日から友だちだね…！」@<fn>{anne}と言っている気分になってきましたが、例え相手が自分自身だろうが友だちは友だちです！メッセージを送ってみましょう。先ほどと同じように［メッセージを配信する］をタップします。

//footnote[anne][食器を仕舞った本棚のガラス戸に映った自分をケティ・モーリスと呼んで仲良くしています。早くダイアナに出会いたいですね。]

［追加］をタップして、先ずは［テキスト］を選び、適当なテキストを入力します。（@<img>{send-message-via-app-again}）

//image[send-message-via-app-again][［追加］から［テキスト］を選んでテキストを入力する][scale=0.8]{
//}

さらに［追加］をタップして、今度は［スタンプ］を選び、［スタンプを選択］から適当なスタンプを選びます。（@<img>{send-message-via-app-again-2}）

//image[send-message-via-app-again-2][［追加］して適当なスタンプを選択する][scale=0.8]{
//}

これでどんなメッセージが送られるのか、右上の［プレビュー］から確認してみましょう。（@<img>{preview-message-again-1}）

［トークルーム］では、こんな感じの見た目になるようです。［トークリスト］をタップすると、トークの一覧画面での見え方も確認できます。さっきより念押しが強めなメッセージが準備できました。見え方を確認したら、いったんプレビューは右上の［×］で閉じましょう。

//image[preview-message-again-1][右上の［プレビュー］からトークルームやトークリストでの見え方を確認しよう][scale=1]{
//}

［次へ］をタップして、そのまま［すべての友だち］に送ってみましょう。さっきは誰にも届きませんでしたが、いまはたったひとりの友だちに届くはずです。私に届け！私のメッセージ…！祈りを込めて［配信］をタップします。（@<img>{send-message-via-app-again-3}）

//image[send-message-via-app-again-3][［すべての友だち］にメッセージを［配信］する][scale=0.8]{
//}

ピロン！LINEの通知が来ました！新刊の購入をお願いするメッセージが届いたようです。（@<img>{got-a-message}）

//image[got-a-message][LINE公式アカウントからメッセージが届いた！][scale=0.6]{
//}

やったね！これで「LINE公式アカウントから友だちにメッセージを送る」というアチーブメントを達成しました。

===[column] 【コラム】LINE公式アカウントのメッセージはさかのぼって見られる？

LINE公式アカウントと友だちになると、メッセージが届くようになりますが、友だちになる以前のメッセージはさかのぼって見られるのでしょうか？

残念ながらメッセージが届くのは友だちになってからなので、友だちになる以前に送信されていたLINE公式アカウントのメッセージを、TwitterやInstagramのようにさかのぼって見ることはできません。

LINE公式アカウントから友だちへメッセージを送るときに、同内容をLINE VOOMにも投稿していれば、そちらはさかのぼって見られます。

===[/column]

//pagebreak

===[column] 【コラム】メッセージの通数はどうカウントされるのか

たとえば1人の友だちに対してLINE公式アカウントから、こんなふうにテキストと画像とスタンプという3つのメッセージオブジェクト@<fn>{object}が含まれるメッセージを送った場合、メッセージの通数は1通でしょうか？それとも3通でしょうか？（@<img>{three-message-objects}）

//image[three-message-objects][テキストと画像とスタンプのメッセージ][scale=0.4]{
//}

メッセージの通数は送信対象となった友だちの人数でカウントされるので、このように3つのメッセージオブジェクトをまとめて送った場合でも、カウントは1通となります。もしテキストを送る、画像を送る、スタンプを送る、というようにメッセージを3回に分けて送ったらカウントは3通ですね。ちなみに1つのメッセージにつきメッセージオブジェクトはLINE Official Account Managerや管理アプリでは最大3つ、Messaging APIでは最大5つまで指定できます。

メッセージは友だちとLINE公式アカウントの1対1のトークだけでなく、何人もの友だちが参加しているグループトークに対しても送信可能です。前述のとおり、メッセージの通数は送信対象となった友だちの人数でカウントされるので、友だち3人とLINE公式アカウントが参加しているグループトークに、LINE公式アカウントからメッセージを送った場合、メッセージの通数は3通としてカウントされます。

なおどんなメッセージでも無料メッセージの通数を消費する訳ではありません。友だち追加されたときのあいさつメッセージや、Webhook@<fn>{webhook}に含まれる応答トークンを使って送る応答メッセージなどは、何通送っても通数としてカウントされません。@<fn>{free-message}

===[/column]

//footnote[object][「なんかさらっと出てきたけどメッセージオブジェクトってなんなんですの？わたくし分かりませんわ！」「遠方のご学友にお手紙を出すときのことを想像なさって。封筒にお気持ちをしたためた便箋を入れて、お茶会でお撮りあそばした思い出の写真も入れて、贈り物のぷくぷくファンシーシールも入れますでしょ？その便箋や写真やシール、ひとつひとつがメッセージオブジェクトなんですわ！」「なるほどですわ！便箋と写真とシールは、テキストと画像とスタンプの比喩ですわね！ところでどうしてわたくしたち、突然お嬢様なんですの？」「説明しにくいことはお嬢様になるとなぜかうまいこと説明できるんですわ！」]
//footnote[webhook][Webhookや応答トークンについては、@<hd>{article02|webhook}で後述します。]
//footnote[free-message][課金対象となるメッセージについて｜LINE for Business @<href>{https://www.linebiz.com/jp/service/line-official-account/plan/}]

==={try-message} LINE公式アカウントにメッセージを送ってみる

LINE公式アカウントからメッセージで「絶対に新刊買ってね！」と頼まれたので、ここで「新刊買います！」と返事をしてあげたいのですが、LINE公式アカウントに返事を送ったらいったいどうなるのでしょうか？物は試しです。LINEで、LINE公式アカウントに対してメッセージを送ってみましょう。

LINE公式アカウントに「新刊買います！」とメッセージを送ってみたところ、なんとまたしても設定した覚えのない「申し訳ありませんが、このアカウントでは個別のお問い合わせを受け付けておりません」というメッセージが返ってきました。誰だお前！私が作ったLINE公式アカウントで勝手に返事してきて誰なんだ。（@<img>{reply-message}）

//image[reply-message][メッセージを送ったら「応答メッセージ」が届いた][scale=0.4]{
//}

これはLINE公式アカウントの「応答メッセージ@<fn>{reply-message}」という機能で、ユーザーからメッセージが届いたときに、自動で任意の返答を送ることができます。LINE公式アカウントを作ると、デフォルトで「応答メッセージ」が設定されているので、このメッセージが届いたという訳です。

//footnote[reply-message][応答メッセージについては、@<hd>{article02|reply}で後述します。]

//pagebreak

== LINE公式アカウントの基礎知識

無事にLINE公式アカウントから友だちへのメッセージ送信もできたので、ここでちょっとLINE公式アカウントについていくつか説明をしておきましょう。実践の後の座学タイムです。

=== LINE公式アカウントと普通のLINEアカウントとの違い

先ほどLINEアカウントとLINE公式アカウントは別物という話をしましたが、普通のLINEアカウントとLINE公式アカウントはどうやったら見分けをつけられるのでしょうか？LINE公式アカウントを運用している本人にはもちろん分かりますが、どちらもQRコードを読み込んで友だち追加できるので、友だちになる側はどこで「あ、これLINE公式アカウントだ」と気づけるのでしょう？

友だち追加の画面を比較してみましょう。左がLINE公式アカウントで、右が普通のLINEアカウントです。（@<img>{line-official-account-and-line-account}）

//image[line-official-account-and-line-account][左がLINE公式アカウントで、右が普通のLINEアカウント][scale=0.75]{
//}

LINE公式アカウントの友だち追加画面には追加、投稿のボタンが並んでいますが、普通のLINEアカウントの友だち追加画面だと追加、ブロック、通報のボタンが並んでいます。またLINE公式アカウントの方は、ベーシックID@<fn>{basic}が表示されていたり、［ほかの公式アカウントを見る］や［友だち限定の情報をゲット］とあるので、よく見れば「これ、LINE公式アカウントだな？」と気づけそうです。

//footnote[basic][ベーシックIDについては、@<hd>{article01|premium-and-basic}で後述します。]

トークルームの画面も比較してみましょう。LINE公式アカウントは名前の左に「未認証@<fn>{not-verified}のLINE公式アカウント」であることを示す灰色のバッジが付いています。（@<img>{line-official-account-and-line-account-2}）

//footnote[not-verified][未認証アカウントについては、@<hd>{article01|badge}で後述します。]

//image[line-official-account-and-line-account-2][LINE公式アカウントは名前の左に灰色のバッジが付いている][scale=0.8]{
//}

普通のLINEアカウントとLINE公式アカウントには、このような見た目の違いがあります。

==={premium-and-basic} プレミアムIDとベーシックID

LINE公式アカウントを作ると、最初に「ベーシックID」というものが自動で割り振られます。@マークと、ランダムな3桁の数字と5桁の英字で構成された「@880xrymm」みたいなものがベーシックIDです。

LINEの検索窓でこのベーシックIDを検索（@<img>{id-search}）すると、ちゃんとLINE公式アカウントにたどり着けるのですが、友だち登録してもらうためにランダムな文字列をユーザーに「最初が@で…880の…えっくすあーる…わい…えむえむ」のように伝えて入力させるのはなかなか難儀です。もうちょっと名前っぽい、覚えやすいIDがほしくなりますよね。

//image[id-search][友だち検索でベーシックIDを検索するとLINE公式アカウントが表示される][scale=0.5]{
//}

そこでなんと、月額100円（税別）を出せば、4文字から18文字で希望の「プレミアムID@<fn>{premium}」というものが取得できます！ただし、他の人がすでに使っているプレミアムIDは取得できません。

//footnote[premium][プレミアムIDとは｜LINE for Business　　　　　　　　　　　　　　　　　　　　　　　　　 @<href>{https://www.linebiz.com/jp/service/line-official-account/plan/}]

プレミアムIDと有料プランは別枠なので、無料のコミュニケーションプランのまま、プレミアムIDだけ購入することも可能です。またプレミアムIDを取得しても、ベーシックIDや、プレミアムID取得前に作った友だち追加のURL、QRコードなどは引き続き使用できます。

==={badge} 未認証アカウントと認証済アカウント

無料プランと有料プラン、ベーシックIDとプレミアムIDについてはすでに説明しましたが、実はさらに認証ステータスというものがあり、LINE公式アカウントは未認証アカウントと認証済アカウント@<fn>{verified}の2種類に分けられます。

//footnote[verified][「認証済アカウント」とは？｜メリット・申請方法｜LINE for Business @<href>{https://www.linebiz.com/jp/service/line-official-account/verified-account/}]

認証済アカウントになるためには申請をして、審査に通過する必要がありますが、この申請と審査は無料です。有料プランやプレミアムIDと違って、認証済アカウントになるために費用はかかりません。

では認証済アカウントになると何がうれしいのでしょう？

認証済アカウントになると、バッジの色が灰色から青色になってついて「公式っぽさ」が増すと共に、LINE内でアカウント名や概要が検索対象@<fn>{account-name}になり、検索結果に表示されるようになります。@<fn>{search}逆に言えば、デフォルトの未認証アカウントであれば、友だち追加のQRコードやURL、ベーシックID、あるいはプレミアムIDを自ら露出しない限り、知らない人から勝手に友だち追加される可能性は低いということです。

//footnote[account-name][未認証アカウントの場合、アカウント名や概要に含まれる単語で検索しても検索結果には出てきません。ですが、ベーシックIDやプレミアムIDで検索した場合は、@<hd>{article01|premium-and-basic}のとおり、未認証アカウントであってもしっかり検索結果に表示されます。]
//footnote[search][厳密に言えば、認証済アカウントになると検索結果に表示させるのか、非表示にしておくのかを選べるようになります。たとえば「お金を払って謎解きゲームのチケットを買った人だけ、LINE公式アカウントと友だちになって、LINEのトークからゲームに参加できる」というようなことを実現したい場合は、認証済アカウントであっても検索結果には表示されないよう「非表示」を選んでおきましょう。 @<href>{https://www.linebiz.com/jp/manual/OfficialAccountManager/tutorial-step5/}]

また認証済アカウントになると、「友だち募集中」と書かれたキャラクターとQRコード付きのステッカー、三角POPなどが購入できます。お店の入り口に貼ったり、テーブルに置いたりして、友だち追加を促すためのおしゃれな販促物を、わざわざ自分で作らなくても簡単に購入できるのがいいところですね。

ただし認証済アカウントの審査は、個人名では通らない@<fn>{verified-check}ようです。販促物が購入できる、という特典を見ても、認証済アカウントはインフルエンサーなどの個人@<fn>{influencer}ではなく、店舗やサービスなどをターゲットとしているようです。

//footnote[verified-check][LINE公式アカウントの審査とは｜認証済アカウント申請時の注意点 @<href>{https://www.linebiz.com/jp/column/technique/20190829/}]
//footnote[influencer][ちなみに2022年6月には「LINEクリエイターアカウント」という、インフルエンサーやクリエイター向けのLINE公式アカウントの新カテゴリーも発表されていました。 @<href>{https://linecorp.com/ja/pr/news/ja/2022/4265}]

===[column] 【コラム】準備中のLINE公式アカウントをリリース日まで非公開にしておける？

準備中のLINE公式アカウントが人目に触れてしまうことのないよう、リリース日まではアカウントそのものを非公開にしておきたい！と思ったとします。そんなことは可能なのでしょうか？

残念ながらLINE公式アカウントには「非公開」と「公開」、あるいは「開発中」と「リリース済み」というような状態管理がありません。作られた瞬間から、ベーシックIDやプレミアムIDさえ分かれば、実態がリリース前だろうがなんだろうが誰でも友だち追加できてしまいます。

リリース前や準備用のLINE公式アカウントは、うっかりベーシックIDやプレミアムID、そして友だち追加のURLなどを外部に露出させないよう注意しましょう。また認証済アカウントにした場合は、「検索結果での表示」をデフォルトの「非表示」のままにしておきましょう。

===[/column]
