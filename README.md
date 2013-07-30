#Akari's Counter Attack(ACA)
2次創作同人ゲームのソースコードです。
バックアップ目的であげました。
Controller.hppだけ他の人が書きました。それ以外は自分です。

##制作環境
 * OS Windows 7 32bit
 * IDE Visal Studio 2010
 * 言語 C++11
 * API DXライブラリ(DirectX9 + Win32API)

##ファイル構成

###ゲームロジック
名前空間`aca::game`に属します

 * Boss1 1面ボスのクラスです
 * Boss2 2面ボスのクラスです
 * Boss3 3面ボスのクラスです
 * Collision 衝突判定をするクラスです
 * CollisionMap 複数のCollisionを管理するクラスです
 * DynamicObject 動くオブジェクトの基底クラスです
 * Enemy 敵の基底クラスです
 * Player プレイヤーのクラスです
 * Lazer レーザー弾のクラスです
 * LazerList 複数のLazerを管理するクラスです
 * Life キャラクターのライフのクラスです
 * Position 座標クラスです
 * GameState ゲームのメインロジックです。キー入力を内部へ伝えたり、描画関数を呼び出します。
 * Weapon 弾のクラスです
 * WeapoList 複数のWeaponを管理するクラスです

###リソース管理
名前空間`aca::resource`に属します

 * Animation 画像のアニメーションを管理するクラスです
 * DXImage DXライブラリを用いた画像管理クラスです
 * Image 画像管理クラス。実装はテンプレート引数に渡されたクラスへ委譲します。インターフェイスを提供します。
 * Sound 音声管理クラス。時間がなかったためその場しのぎの実装に。


###シーケンス遷移
名前空間`aca::scene`に属します。
それより下のレイヤーにゲーム自体のシーン遷移があり、`aca::scene::game`に属します
  
メインシーン

 * Main メインシーン全体を管理するクラスです。
 * MainScene メインシーンクラスのインターフェイスです
 * Ending エンディングのシーンクラスです。
 * Title タイトルのシーンクラスです。
  
ゲームシーン

 * Game ゲームシーン全体を管理するクラスです
 * GameScene ゲームシーンクラスのインターフェイスです
 * Clear ステージクリアのシーンクラスです
 * Failure 負けた時のシーンクラスです
 * Play ゲームプレイ中のシーンクラスです
 * Ready ゲームプレイ開始時の開始前カウントダウンのシーンクラスです

###その他
その他のクラス等です

 * Config ゲーム全体で使う定数を宣言しています
 * Controller DXライブラリを用いた仮想コントローラクラスです。他人が書きました。
 * Fps ゲームのFPSを管理するクラスです
 * IObserver Observerパターンを実装するためのインターフェイスです
 * WinMain メイン関数数が書かれています

##ライセンス
boostを使用していれば[boost software license](http://www.boost.org/users/license.html)に従います。
Controller.hppのみ他人作成であり、無断での改変コピー使用等を禁止します。