#if 0
[前提]
*使うには
    - 使いたいソースコードで#include "Controller.hpp"
    - 下に書いた感じでアクセス
    - お　わ　り

    * アクセス
    - 基本的にController::getInstance(番号)って書けば,グローバル変数の気分でアクセス可能
    - コードが汚くなるので,Controller *input = Controller::getInstance(番号);
とか書くと input->ボタン(A).押してる？();って感じでアクセスできて,ちょっと綺麗かも.ポインタ操作なので,コストは誤差．

    * インスタンスの生成
    - Controller::getInstance(ゲームパッドの番号)で,パッドごとに1個だけ作成される.
    - DXライブラリ側で16個まで対応してるっぽいので上限は16個.

    * ユーザーが直接使うクラスはControllerだけ

    [公開メソッド]

【よく使いそうなもの】
    * Controller::getInstance(int padnum)
    - 仮想コントローラーのインスタンスを指すポインタを返す関数
    - 何度実行しても,パッド１つにつきインスタンスは1個しか生成されない
    - いわゆるシングルトンパターンっぽいもの

    * Update()
    - 更新処理.毎フレーム1回だけメインループで実行してください.

    * GetButton( DX_BUTTON buttons )
    - ボタンへの参照を返す．ボタンの情報を取ってくるだけ．
    - ボタンは、押されているか(isHitkey),押した瞬間か(isPush),離した瞬間か(isRelease)を調べられる.
    - また、GetPushCount()で何フレームの間押しっぱなしかも取得できる.

    * SetButton(DX_BUTTON buttons,int key,int pad)
    - 仮想コントローラーのボタンにキーボードのキーと,パッドのボタンを割り当てる
    - 引数であるkey/padに入れるのはDXライブラリ標準のキーインプット/パッドインプット用の定数(KEY_INPUT_UPとかPAD_INPUT_UPとか)

    サンプルコードは以下

#include "Controller.hpp"

    int test(){
        // 初めて実行した時にはインスタンスを生成してそのポインタを返し、
        // 二回目以降は既に存在しているインスタンスを返す。
        // (=普通に作ろうとしても、コンストラクタがprivateなので作成できない)
        // 一個しかインスタンス作れないグローバル変数みたいな扱いでおｋ
        Controller* input = Controller::GetInstance( 1 );

        // こういう風に使ってもよい
        Controller::GetInstance( 1 )->Update();

        // 仮想ボタン(DX_BUTTON::なんか)に、実際のキーボードのキーと、ジョイパッドのボタンを割り当てる
        // SetButton( 仮想ボタン, DXライブラリで決められているキーボードのキーの値, DXライ(略)パッドのボタンの値);

        // 仮想コントローラー(1P)の上キーに、キーボードの上とパッド(1P)の上を設定
        input->SetButton( BUTTON_UP, KEY_INPUT_UP, PAD_INPUT_UP);
        // 仮想コントローラー(1P)の下キーに、キーボードの下とパッド(1P)の下を設定
        input->SetButton( BUTTON_DOWN, KEY_INPUT_DOWN, PAD_INPUT_DOWN);
        // 仮想コントローラー(1P)の左キーに、キーボードの左とパッド(1P)の左を設定
        input->SetButton( BUTTON_LEFT, KEY_INPUT_LEFT, PAD_INPUT_LEFT);
        // 仮想コントローラー(1P)の右キーに、キーボードの右とパッド(1P)の右を設定
        input->SetButton( BUTTON_RIGHT, KEY_INPUT_RIGHT, PAD_INPUT_RIGHT);
        // 仮想コントローラー(1P)のＡキーに、キーボードのＺとパッド(1P)のボタンAを設定
        input->SetButton( BUTTON_A, KEY_INPUT_Z, PAD_INPUT_A );
        // 仮想コントローラー(1P)のＢキーに、キーボードのＸとパッド(1P)のボタンBを設定
        input->SetButton( BUTTON_B, KEY_INPUT_X, PAD_INPUT_A );

        // メインループ（とする）
        while(true){
            // Updateを行ったタイミングでキー/パッドの入力状況を更新する
            input->Update();

            if( input->GetButton( BUTTON_A ).IsHitKey() ){
                // 仮想コントローラのボタン:BUTTON_Aが押されているなら、ここの処理が行われる
            }
            if( input->GetButton( BUTTON_B ).IsPush() ){
                // 仮想コントローラのボタン:BUTTON_Bが押された瞬間(フレーム)なら、ここの処理が行われる
            }
            if( input->GetButton( BUTTON_DOWN ).IsPush() ){
                // 仮想コントローラのボタン:BUTTON_DOWNが離された瞬間(フレーム)なら、ここの処理が行われる
            }

        }
}


#endif


#pragma once
#include <Dxlib.h>
#include <fstream>
#include <cstdlib>
#include <string>

// 定数：全14種のボタンを設定可能
enum DX_BUTTON{
    BUTTON_UP,BUTTON_DOWN,BUTTON_LEFT,BUTTON_RIGHT,
    BUTTON_A,BUTTON_B,BUTTON_C,
    BUTTON_X,BUTTON_Y,BUTTON_Z,
    BUTTON_L,BUTTON_R,
    BUTTON_START,BUTTON_M,
    DX_BUTTON_END
};

class Controller{
private:
    const int padnum;
    static Controller* instance[DX_INPUT_PAD16];
    struct InputData{
        static const int I_D_SIZE = 256;
        int PadInput;
        char KeyBuff[I_D_SIZE];
        bool button_state[DX_BUTTON_END];
        unsigned int frame;
        // "フレームを除く"要素が一致してるかどうかを調べる
        inline bool operator!=(const InputData& rhs){
            // パッド入力が一致してるかどうか
            if(PadInput == rhs.PadInput){
                // キーボード入力が一致してるかどうか
                for(int i=0; i<I_D_SIZE; ++i){
                    if(KeyBuff[i] != rhs.KeyBuff[i]){ return true;}
                }
                return false;
            }
            else{
                return true;
            }
        }
    } now_frame_input;
    struct Button{
        DX_BUTTON name;
        unsigned key;
        unsigned pad;
        unsigned timer;
        bool push_now;
        bool release_now;
        bool hit;
        Button() : name(DX_BUTTON_END),pad(0U),key(0U),timer(0U), push_now(false),release_now(false),hit(false){}

        inline void StateInit(){push_now=false; release_now=false; hit=false;}
        inline bool Update(const InputData& data){
            bool keyhit_flag  = ((data.PadInput & pad) != 0) || (data.KeyBuff[key] != 0);
            if( keyhit_flag ){
                if(timer == 0){
                    push_now = true;
                    release_now = false;
                }
                else{
                    push_now = false;
                }
                timer++;
                hit = true;
            }
            else{
                if(timer != 0){
                    release_now = true;
                    push_now = false;
                    timer = 0;
                }else{
                    release_now = false;
                }
                hit = false;
            }
            return keyhit_flag;
        }
    public:
        inline const bool	IsHitKey() const	{return hit;}
        inline const bool	IsPush() const	{return push_now;}
        inline const bool	IsRelease() const	{return release_now;}
        inline const int	GetPushCount() const {return timer;}
    } button[DX_BUTTON_END];
public:
    static Controller *GetInstance(int PADNUM){
        // 想定外のパッド番号を呼び出されたらnull-pointerを返す
        if( PADNUM < 1 || 16 < PADNUM){
            return NULL;
        }

        const size_t padnumber = PADNUM-1;
        if( instance[padnumber] != NULL ){
            return instance[padnumber];
        }
        else{
            instance[padnumber] = new Controller(PADNUM);
            return instance[padnumber];
        }
    }

    inline void Update(){
        // 実際に入力を取得している部分
        // ジョイパッドの入力状況をintとして格納
        now_frame_input.PadInput = GetJoypadInputState( padnum );
        // キーボードの入力状況をバッファ
        GetHitKeyStateAll( now_frame_input.KeyBuff ) ;

        // ボタンの状態をアップデートする
        for(int i=0; i < DX_BUTTON_END; i++){
            button[i].Update(now_frame_input);
        }
    }
    inline const Button& GetButton(const DX_BUTTON buttons) const{
        return button[buttons];
    }
    void SetButton(DX_BUTTON buttons,int key,int pad)
    {
        button[buttons].name = buttons;
        button[buttons].key = key;
        button[buttons].pad = pad;
    }

    void SaveConfig(const char* filename, const char* configname, std::ios_base::open_mode mode=std::ios::out)
    {
        std::ofstream ofs(filename,mode);

        ofs << "[" << configname << "]" << std::endl;
        for(size_t i=0U; i < DX_BUTTON_END; ++i){
            ofs << button[i].name << "," << button[i].key << "," << button[i].pad << "," << std::endl;
        }
        ofs << std::endl;
    }

    bool LoadConfig(const char* filename, const char* configname)
    {
        static const int bufsize = 1024;
        std::string target = configname;
        std::ifstream ifs(filename);

        if( !ifs.is_open() ){
            return false;
        }

        while( !ifs.eof() ){
            if( ifs.get() == '['){
                char buf[bufsize];
                ifs.getline(buf,bufsize,']');
                std::string section = buf;
                if( target == section ){
                    for(size_t i=0U; i < DX_BUTTON_END; ++i )
                    {
                        char buf[bufsize];
                        ifs.getline(buf,bufsize,',');
                        button[i].name = static_cast<DX_BUTTON>(std::atoi(buf));
                        ifs.getline(buf,bufsize,',');
                        button[i].key = std::atoi(buf);
                        ifs.getline(buf,bufsize,',');
                        button[i].pad = std::atoi(buf);
                    }
                    return true;
                }
            }
        }
        return false;
    }
private:
    Controller(int PADNUM) : padnum(PADNUM){}
    Controller(const Controller& tmp) : padnum(0){}
    void operator =(const Controller& ins){}

    ~Controller(){}
};

//ヘッダで定義すると多重定義になってしまう！
//Main.cppで定義した。
//Controller* Controller::instance[DX_INPUT_PAD16];