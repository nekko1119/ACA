#if 0
[�O��]
*�g���ɂ�
    - �g�������\�[�X�R�[�h��#include "Controller.hpp"
    - ���ɏ����������ŃA�N�Z�X
    - ���@��@��

    * �A�N�Z�X
    - ��{�I��Controller::getInstance(�ԍ�)���ď�����,�O���[�o���ϐ��̋C���ŃA�N�Z�X�\
    - �R�[�h�������Ȃ�̂�,Controller *input = Controller::getInstance(�ԍ�);
�Ƃ������� input->�{�^��(A).�����Ă�H();���Ċ����ŃA�N�Z�X�ł���,��������Y�킩��.�|�C���^����Ȃ̂�,�R�X�g�͌덷�D

    * �C���X�^���X�̐���
    - Controller::getInstance(�Q�[���p�b�h�̔ԍ�)��,�p�b�h���Ƃ�1�����쐬�����.
    - DX���C�u��������16�܂őΉ����Ă���ۂ��̂ŏ����16��.

    * ���[�U�[�����ڎg���N���X��Controller����

    [���J���\�b�h]

�y�悭�g�������Ȃ��́z
    * Controller::getInstance(int padnum)
    - ���z�R���g���[���[�̃C���X�^���X���w���|�C���^��Ԃ��֐�
    - ���x���s���Ă�,�p�b�h�P�ɂ��C���X�^���X��1������������Ȃ�
    - ������V���O���g���p�^�[�����ۂ�����

    * Update()
    - �X�V����.���t���[��1�񂾂����C�����[�v�Ŏ��s���Ă�������.

    * GetButton( DX_BUTTON buttons )
    - �{�^���ւ̎Q�Ƃ�Ԃ��D�{�^���̏�������Ă��邾���D
    - �{�^���́A������Ă��邩(isHitkey),�������u�Ԃ�(isPush),�������u�Ԃ�(isRelease)�𒲂ׂ���.
    - �܂��AGetPushCount()�ŉ��t���[���̊ԉ������ςȂ������擾�ł���.

    * SetButton(DX_BUTTON buttons,int key,int pad)
    - ���z�R���g���[���[�̃{�^���ɃL�[�{�[�h�̃L�[��,�p�b�h�̃{�^�������蓖�Ă�
    - �����ł���key/pad�ɓ����̂�DX���C�u�����W���̃L�[�C���v�b�g/�p�b�h�C���v�b�g�p�̒萔(KEY_INPUT_UP�Ƃ�PAD_INPUT_UP�Ƃ�)

    �T���v���R�[�h�͈ȉ�

#include "Controller.hpp"

    int test(){
        // ���߂Ď��s�������ɂ̓C���X�^���X�𐶐����Ă��̃|�C���^��Ԃ��A
        // ���ڈȍ~�͊��ɑ��݂��Ă���C���X�^���X��Ԃ��B
        // (=���ʂɍ�낤�Ƃ��Ă��A�R���X�g���N�^��private�Ȃ̂ō쐬�ł��Ȃ�)
        // ������C���X�^���X���Ȃ��O���[�o���ϐ��݂����Ȉ����ł���
        Controller* input = Controller::GetInstance( 1 );

        // �����������Ɏg���Ă��悢
        Controller::GetInstance( 1 )->Update();

        // ���z�{�^��(DX_BUTTON::�Ȃ�)�ɁA���ۂ̃L�[�{�[�h�̃L�[�ƁA�W���C�p�b�h�̃{�^�������蓖�Ă�
        // SetButton( ���z�{�^��, DX���C�u�����Ō��߂��Ă���L�[�{�[�h�̃L�[�̒l, DX���C(��)�p�b�h�̃{�^���̒l);

        // ���z�R���g���[���[(1P)�̏�L�[�ɁA�L�[�{�[�h�̏�ƃp�b�h(1P)�̏��ݒ�
        input->SetButton( BUTTON_UP, KEY_INPUT_UP, PAD_INPUT_UP);
        // ���z�R���g���[���[(1P)�̉��L�[�ɁA�L�[�{�[�h�̉��ƃp�b�h(1P)�̉���ݒ�
        input->SetButton( BUTTON_DOWN, KEY_INPUT_DOWN, PAD_INPUT_DOWN);
        // ���z�R���g���[���[(1P)�̍��L�[�ɁA�L�[�{�[�h�̍��ƃp�b�h(1P)�̍���ݒ�
        input->SetButton( BUTTON_LEFT, KEY_INPUT_LEFT, PAD_INPUT_LEFT);
        // ���z�R���g���[���[(1P)�̉E�L�[�ɁA�L�[�{�[�h�̉E�ƃp�b�h(1P)�̉E��ݒ�
        input->SetButton( BUTTON_RIGHT, KEY_INPUT_RIGHT, PAD_INPUT_RIGHT);
        // ���z�R���g���[���[(1P)�̂`�L�[�ɁA�L�[�{�[�h�̂y�ƃp�b�h(1P)�̃{�^��A��ݒ�
        input->SetButton( BUTTON_A, KEY_INPUT_Z, PAD_INPUT_A );
        // ���z�R���g���[���[(1P)�̂a�L�[�ɁA�L�[�{�[�h�̂w�ƃp�b�h(1P)�̃{�^��B��ݒ�
        input->SetButton( BUTTON_B, KEY_INPUT_X, PAD_INPUT_A );

        // ���C�����[�v�i�Ƃ���j
        while(true){
            // Update���s�����^�C�~���O�ŃL�[/�p�b�h�̓��͏󋵂��X�V����
            input->Update();

            if( input->GetButton( BUTTON_A ).IsHitKey() ){
                // ���z�R���g���[���̃{�^��:BUTTON_A��������Ă���Ȃ�A�����̏������s����
            }
            if( input->GetButton( BUTTON_B ).IsPush() ){
                // ���z�R���g���[���̃{�^��:BUTTON_B�������ꂽ�u��(�t���[��)�Ȃ�A�����̏������s����
            }
            if( input->GetButton( BUTTON_DOWN ).IsPush() ){
                // ���z�R���g���[���̃{�^��:BUTTON_DOWN�������ꂽ�u��(�t���[��)�Ȃ�A�����̏������s����
            }

        }
}


#endif


#pragma once
#include <Dxlib.h>
#include <fstream>
#include <cstdlib>
#include <string>

// �萔�F�S14��̃{�^����ݒ�\
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
        // "�t���[��������"�v�f����v���Ă邩�ǂ����𒲂ׂ�
        inline bool operator!=(const InputData& rhs){
            // �p�b�h���͂���v���Ă邩�ǂ���
            if(PadInput == rhs.PadInput){
                // �L�[�{�[�h���͂���v���Ă邩�ǂ���
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
        // �z��O�̃p�b�h�ԍ����Ăяo���ꂽ��null-pointer��Ԃ�
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
        // ���ۂɓ��͂��擾���Ă��镔��
        // �W���C�p�b�h�̓��͏󋵂�int�Ƃ��Ċi�[
        now_frame_input.PadInput = GetJoypadInputState( padnum );
        // �L�[�{�[�h�̓��͏󋵂��o�b�t�@
        GetHitKeyStateAll( now_frame_input.KeyBuff ) ;

        // �{�^���̏�Ԃ��A�b�v�f�[�g����
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

//�w�b�_�Œ�`����Ƒ��d��`�ɂȂ��Ă��܂��I
//Main.cpp�Œ�`�����B
//Controller* Controller::instance[DX_INPUT_PAD16];