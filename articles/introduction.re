= はじめに

//flushright{

2023年5月
mochikoAsTech

//}

この本を手に取ってくださったあなた、こんにちは、あるいははじめまして。
「LINE Botをつくってみよう ～APIを試して学んでしっかりわかる～」の筆者、mochikoAsTechです。

== 想定する読者層

本書は、こんな人に向けて書かれています。

 * 「APIを叩く」をやってみたい人
 * 「Botを作る」をやってみたい人
 * これからプログラミングを学ぼうと思っている人
 * LINE APIを使ってみたい人
 * LINEでBotを作ってみたい人

== マッチしない読者層

本書は、こんな人が読むと恐らく「not for meだった…（私向けじゃなかった）」となります。

 * コミュニケーションアプリ「LINE（ライン）」を使ったことがなく、LINEの基本操作から知りたい人
 * LINE公式アカウントで友だちをうまく増やす方法を知りたい人
 * LINE Official Account Managerの使い方を詳しく知りたい人
 * LINEで簡単に月20万稼げる！みたいなことがしたい人

== 本書の特徴

本著では実際にLINE公式アカウントからメッセージを送ったり、LINE Botを作ったりします。先に手を動かして試して、続いて裏付けになる事柄を学ぶ、というステップを交互に踏むため、理解がしやすく、プログラミング初心者でも飽きずに読み進められる内容です。

また実際の開発でありがちなトラブルをとり上げて、

 * こんなエラーが起きたら原因はどう調べたらいいのか？
 * 問題をどう解決したらいいのか？
 * どうしたら事前に避けられるのか？

を解説しています。

紙の書籍をお買い上げいただいた方は、フルカラーのPDF版を無料でダウンロードできますので、ぜひご活用ください。詳しくは@<chapref>{postscript}にある@<hd>{postscript|pdf}を参照してください。

== 用語の定義

私たちは「LINE（ライン）」という言葉を、無意識に色んな意味で使っています。

「LINEってやってる？」「うん。でも家族としか使ってない」というときのLINEは、コミュニケーションアプリとしてのLINEアプリのことを指しています。「昨日送ったLINE見た？」「ごめん。寝てた」というときのLINEは、LINEアプリのトーク上でやりとりするメッセージのことを指しています。「LINEってヤフーと合併するんでしょ」「そうなんだ」というときのLINEは、LINE株式会社のことを指しています。「お支払いは何になさいますか？」「あ、LINEで！」というときのLINEは、スマホで送金や決済ができるLINE Payというサービスを指しています。

こんなふうに、同じ「LINE」という言葉でも文脈によって色んな意味になるため、本書における用語を最初に定義しておきます。

 * 本書では、LINEアプリのことを「LINE」と呼びます。ただ「LINE」とだけ書いてあったら、これはLINEアプリのことだな、と思ってください。
 * LINEアプリのトーク上でやりとりするメッセージのことは、「メッセージ」と呼びます。
 * 会社としてのLINEは、「LINE株式会社」と呼びます。
 * それ以外の各サービスは「LINE Pay」のような正式名称で呼びます。

== 用意するもの

 * LINEの入ったスマートフォン

== 本書のゴール

本書を読み終わると、このような状態になっています。

 * LINE Botの仕組みを理解している
 * LINE Botを作るときに何を準備すればいいか分かっている
 * プロバイダーやチャネルに何を登録すべきか分かっている
 * 読む前よりLINE APIが好きになっている

== 免責事項

本書に記載された社名、製品名およびサービス名は、各社の登録商標または商標です。

筆者はLINE株式会社に所属していますが、本書は個人として執筆したものであり、本書に記載されている内容はいずれも所属する組織の公式見解ではありません。また、本書は一般に開示されている情報を元に書かれており、筆者が所属する組織において知り得た情報は含まれていません。LINE APIについて言及するにあたって、所属を隠した宣伝であると誤解されないよう所属組織をここに明記しておきます。

本書はできるだけ正確を期すように努めましたが、筆者が内容を保証するものではありません。よって本書の記載内容に基づいて読者が行なった行為、及び読者が被った損害について筆者は何ら責任を負うものではありません。

不正確あるいは誤認と思われる箇所がありましたら、必要に応じて適宜改訂を行いますのでGitHubのIssueやPull requestで筆者までお知らせいただけますと幸いです。

@<href>{https://github.com/mochikoAsTech/startLINEBot}
