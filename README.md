#Akari's Counter Attack(ACA)
2���n�쓯�l�Q�[���̃\�[�X�R�[�h�ł��B
�o�b�N�A�b�v�ړI�ł����܂����B
Controller.hpp�������̐l�������܂����B����ȊO�͎����ł��B

##�����
 * OS Windows 7 32bit
 * IDE Visal Studio 2010
 * ���� C++11
 * API DX���C�u����(DirectX9 + Win32API)

##�t�@�C���\��

###�Q�[�����W�b�N
���O���`aca::game`�ɑ����܂�

 * Boss1 1�ʃ{�X�̃N���X�ł�
 * Boss2 2�ʃ{�X�̃N���X�ł�
 * Boss3 3�ʃ{�X�̃N���X�ł�
 * Collision �Փ˔��������N���X�ł�
 * CollisionMap ������Collision���Ǘ�����N���X�ł�
 * DynamicObject �����I�u�W�F�N�g�̊��N���X�ł�
 * Enemy �G�̊��N���X�ł�
 * Player �v���C���[�̃N���X�ł�
 * Lazer ���[�U�[�e�̃N���X�ł�
 * LazerList ������Lazer���Ǘ�����N���X�ł�
 * Life �L�����N�^�[�̃��C�t�̃N���X�ł�
 * Position ���W�N���X�ł�
 * GameState �Q�[���̃��C�����W�b�N�ł��B�L�[���͂�����֓`������A�`��֐����Ăяo���܂��B
 * Weapon �e�̃N���X�ł�
 * WeapoList ������Weapon���Ǘ�����N���X�ł�

###���\�[�X�Ǘ�
���O���`aca::resource`�ɑ����܂�

 * Animation �摜�̃A�j���[�V�������Ǘ�����N���X�ł�
 * DXImage DX���C�u������p�����摜�Ǘ��N���X�ł�
 * Image �摜�Ǘ��N���X�B�����̓e���v���[�g�����ɓn���ꂽ�N���X�ֈϏ����܂��B�C���^�[�t�F�C�X��񋟂��܂��B
 * Sound �����Ǘ��N���X�B���Ԃ��Ȃ��������߂��̏ꂵ�̂��̎����ɁB


###�V�[�P���X�J��
���O���`aca::scene`�ɑ����܂��B
�����艺�̃��C���[�ɃQ�[�����̂̃V�[���J�ڂ�����A`aca::scene::game`�ɑ����܂�
  
���C���V�[��

 * Main ���C���V�[���S�̂��Ǘ�����N���X�ł��B
 * MainScene ���C���V�[���N���X�̃C���^�[�t�F�C�X�ł�
 * Ending �G���f�B���O�̃V�[���N���X�ł��B
 * Title �^�C�g���̃V�[���N���X�ł��B
  
�Q�[���V�[��

 * Game �Q�[���V�[���S�̂��Ǘ�����N���X�ł�
 * GameScene �Q�[���V�[���N���X�̃C���^�[�t�F�C�X�ł�
 * Clear �X�e�[�W�N���A�̃V�[���N���X�ł�
 * Failure ���������̃V�[���N���X�ł�
 * Play �Q�[���v���C���̃V�[���N���X�ł�
 * Ready �Q�[���v���C�J�n���̊J�n�O�J�E���g�_�E���̃V�[���N���X�ł�

###���̑�
���̑��̃N���X���ł�

 * Config �Q�[���S�̂Ŏg���萔��錾���Ă��܂�
 * Controller DX���C�u������p�������z�R���g���[���N���X�ł��B���l�������܂����B
 * Fps �Q�[����FPS���Ǘ�����N���X�ł�
 * IObserver Observer�p�^�[�����������邽�߂̃C���^�[�t�F�C�X�ł�
 * WinMain ���C���֐�����������Ă��܂�

##���C�Z���X
boost���g�p���Ă����[boost software license](http://www.boost.org/users/license.html)�ɏ]���܂��B
Controller.hpp�̂ݑ��l�쐬�ł���A���f�ł̉��σR�s�[�g�p�����֎~���܂��B