#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include "Includes/Esp.h"
#include "Includes/Hook.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")
#define targetLibName1 OBFUSCATE("libunity.so")

#include "Includes/Macros.h"
#define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)



// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
             OBFUSCATE("Category_FUNÇÕES"),//0 //Not counted
             OBFUSCATE("ButtonLink_ATUALIZAÇÃO _https://bityli.com/IEblP"),//1
             OBFUSCATE("Category_Menu Aim"),//2 //Not counted
             OBFUSCATE("Toggle_AimBot"),//3
             OBFUSCATE("Toggle_AimBot Auto"),//4
             OBFUSCATE("Toggle_AimBot Tiro"),//5
             OBFUSCATE("Toggle_AimBot Mira"),//6
             OBFUSCATE("Toggle_AimBot Agachado"),//7
             OBFUSCATE("Toggle_AimBot Iginorar"),//8
             OBFUSCATE("Toggle_AimBot Ivisivel"),//9
             OBFUSCATE("SeekBar_AimFov_0_360"),//10
             OBFUSCATE("Category_Menu Esps"),//11 //Not counted
             OBFUSCATE("Toggle_Esp Raio"),//12
             OBFUSCATE("Toggle_Esp Draw"),//13
             OBFUSCATE("Toggle_Esp Nome"),//14
             OBFUSCATE("Toggle_Esp Fire"),//15
             OBFUSCATE("Toggle_Esp Distancia"),//16
             OBFUSCATE("Category_Menu Mapa"),//17 //Not counted
             OBFUSCATE("Toggle_Zé Pedrinha"),//18
             OBFUSCATE("Toggle_Teleporte Inimigo"),//19
             OBFUSCATE("Toggle_Gosth Hack"),//20
             OBFUSCATE("Toggle_Fly Hack"),//21
             OBFUSCATE("Toggle_Remover Paraquedas"),//22
             OBFUSCATE("Category_Menu Arma"),//23 //Not counted
             OBFUSCATE("Toggle_Recarga Rapida"),//24
             OBFUSCATE("SeekBar_Chuva De Balas_0_30"),//25
             OBFUSCATE("Toggle_Sem Mira"),//26
             OBFUSCATE("Toggle_Mira Branca"),//27
             OBFUSCATE("Toggle_Sem Som Arma"),//28
             OBFUSCATE("Toggle_Linha Arma"),//29

            OBFUSCATE("RichTextView_ESPEREM AS ATUALIZAÇÕES"
                      "<u> SE INSCREVAM </u>"
                      "<br /> NO CANAL <font color='red'>HACKUDO GAMER</font>"),
            OBFUSCATE("RichWebView_<html><head><style>body{color: white;}</style></head><body>"
                      "<marquee style=\"color: green; font-weight:bold;\" direction=\"left\" scrollamount=\"5\" behavior=\"scroll\">"
                      " A GARENA VAI PIRAR COM ESTE MOD GRÁTIS</marquee>"
                     "</body></html>"),
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

struct My_Patches {
///novas funcoes
    MemoryPatch FlyCarro;
    MemoryPatch TeleportCarro;
    MemoryPatch Speed;
    MemoryPatch Speed2x;
    MemoryPatch Speed3x;
    MemoryPatch Speed4x;
    MemoryPatch Speed5x;
    MemoryPatch speedx250;
    MemoryPatch Underground1;
    MemoryPatch Underground2;
    MemoryPatch Speedcarro1;
    MemoryPatch Speedcarro2;
    MemoryPatch Speedcarro3;
    MemoryPatch Speedcarro4;
    MemoryPatch Speedcarro5;
    MemoryPatch WallCarro;
    MemoryPatch ZePedrinha;


    MemoryPatch LluviaDeBalas1;//0
    MemoryPatch LluviaDeBalas2;//0
    MemoryPatch LluviaDeBalas3;//0
    MemoryPatch LluviaDeBalas4;//0
    MemoryPatch LluviaDeBalas5;//0
    MemoryPatch LluviaDeBalas6;//0
    MemoryPatch LluviaDeBalas7;//0
    MemoryPatch LluviaDeBalas8;//0
    MemoryPatch LluviaDeBalas9;//0
    MemoryPatch LluviaDeBalas10;//0
    MemoryPatch LluviaDeBalas11;//0
    MemoryPatch LluviaDeBalas12;//0
    MemoryPatch LluviaDeBalas13;//0
    MemoryPatch LluviaDeBalas14;//0
    MemoryPatch LluviaDeBalas15;//0
    MemoryPatch LluviaDeBalas16;//0
    MemoryPatch LluviaDeBalas17;//0
    MemoryPatch LluviaDeBalas18;//0
    MemoryPatch LluviaDeBalas19;//0
    MemoryPatch LluviaDeBalas20;//0
    MemoryPatch SilenciarDisparos;
    MemoryPatch RemoverMiras;//01
    MemoryPatch MunicionesIlimitadas;//02
    MemoryPatch VelocidadDeDisparo1;//03
    MemoryPatch VelocidadDeDisparo2;//03
    MemoryPatch VelocidadDeDisparo3;//03
    MemoryPatch RecargaRapida;//04
    MemoryPatch CambioRapidoDeArma;//05
    MemoryPatch ReducirLag;//07
    MemoryPatch DisparosEnMovimiento;//08
    MemoryPatch DisparosAutomaticos;//09
    MemoryPatch TeletransportarCarro1;//10
    MemoryPatch TeletransportarCarro2;//10
    MemoryPatch MatarATodosEnElLobby;//11
    MemoryPatch ModoFantasma;//12
    MemoryPatch FantasmaVeloz1;//13
    MemoryPatch FantasmaVeloz2;//13
    MemoryPatch VelocidadDeCorrer1;//14
    MemoryPatch VelocidadDeCorrer2;//14
    MemoryPatch VelocidadDeCorrer3;//14
    MemoryPatch VelocidadDeCorrer4;//14
    MemoryPatch VelocidadDeCorrer5;//14
    MemoryPatch CuerposBlancos1;//15
    MemoryPatch CuerposBlancos2;//15
    MemoryPatch ModificarCuerpoDeEnemigos1;//16
    MemoryPatch ModificarCuerpoDeEnemigos2;//16
    MemoryPatch ModificarCuerpoDeEnemigos3;//16
    MemoryPatch SensibilidadBaja;
    MemoryPatch SensibilidadMedia;
    MemoryPatch SensibilidadAlta;
    MemoryPatch EnPrimeraPersona;//17
    MemoryPatch MedikitCorriendo1;//18
    MemoryPatch MedikitCorriendo2;//18
    MemoryPatch ModoNoche;//19
    MemoryPatch MapaNegro;//20
    MemoryPatch MapaBlanco;
    MemoryPatch TranspasarPiedras;//21
    MemoryPatch CarroTranspasaParedes1;//22
    MemoryPatch CarroTranspasaParedes2;//23
    MemoryPatch EliminarArboles;//24
    MemoryPatch ElimimarGrama;//25
    MemoryPatch ModoFullHd;//26
    MemoryPatch AmpliarVista1;//27
    MemoryPatch AmpliarVista2;//28
    MemoryPatch AmpliarVista3;//29
    MemoryPatch AmpliarVista4;
    MemoryPatch AmpliarVista5;
    MemoryPatch AmpliarVista6;
    MemoryPatch CaerEn360;//30
    MemoryPatch DiamantesInfinitos;//31
    MemoryPatch OroInfinito;//32
    MemoryPatch LikesInfinitos;//33
    MemoryPatch SerHeroico;//34
    MemoryPatch PrimeiraPessoa;//35
    MemoryPatch AntLogs;//36

    //(desatualizados)))

} hexlibPatches;


bool KMHack1 = false,
        KMHack2 = false,
        KMHack3 = false,
        KMHack4 = false,
        KMHack5 = false,
        KMHack6 = false,
        KMHack7 = false,
        KMHack8 = false,
        KMHack9 = false,
        KMHack10 = false,
        KMHack11 = false,
        KMHack12 = false,
        KMHack13 = false,
        KMHack14 = false,
        KMHack15 = false,
        KMHack16 = false,
        KMHack17 = false,
        KMHack18 = false,
        KMHack19 = false,
        KMHack20 = false,
        KMHack21 = false;

int Desativer = 0;

struct {

    float Fov_Aim = 0.998f;
    int semihs = 0;
    bool aimBotFov = false;
    bool aimScope = false;
    bool aimTiro = false;
    bool hs100 = false;
    bool ghost = false;
    bool hs70 = false;
    bool aimAgachado = false;
    bool aimBody = false;
    bool aimbotauto = true;
    bool teleKill = false;
    bool Paraquedas = false;
    bool aimVisibilidade = false;

    bool AlertWorld = false;
    bool AlertAround = false;
    bool espLine = false;
    bool DISTANCECENTER = false;
    bool espName = false;
    bool espNames = false;
    bool aimFire = false;
    bool espSkeleton = false;
    bool espCircle = false;
    bool espNear = false;
    bool isEspReady = false;

    bool closestEnemy = false;
    bool espFire = false;
    bool Gravity = false;
    bool primeiraPessoa = false;

    bool fakeName = false;
    bool night = false;
    bool sameteams = false;
    bool hd = false;
    bool aimTeste = false;
    bool aimTeste1 = false;
    bool aimTeste3 = false;
    bool medKit = false;
    bool AntLogs = false;


    int FlyCarro = 0;
    int enemyCountAround = 0;
    int botCountAround = 0;
    int enemyCountWorld = 0;
    int botCountWorld = 0;

} MT;

bool active = true;
bool launched = false;

void Changes(JNIEnv *env,
             jobject activityObject,
             jint feature,
             jint Value) {
    __android_log_print(ANDROID_LOG_VERBOSE, "Mod Menu", "Feature: = %d", feature);
    __android_log_print(ANDROID_LOG_VERBOSE, "Mod Menu", "Value: = %d", Value);



    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    switch (feature) {

        case 0:
            break;

        case 1:
            if (Value == 0) {
                MT.hs100 = false;
                MT.hs70 = false;
                MT.aimBody = false;

                LOGI("hs100.hs70.aimBody");
                LOGE("hs100.hs70.aimBody");
                LOGD("hs100.hs70.aimBody");
            } else if (Value == 1) {
                MT.hs70 = false;
                MT.aimBody = false;
                MT.hs100 = !MT.hs100;
                MT.hs100 = true;
                LOGI("hs70.aimBody.hs100.hs100");
                LOGE("hs70.aimBody.hs100.hs100");
                LOGD("hs70.aimBody.hs100.hs100");
            } else if (Value == 2) {
                MT.hs100 = false;
                MT.aimBody = false;
                MT.hs70 = !MT.hs70;
                MT.hs70 = true;
                LOGI("hs100.aimBody.hs70.hs70");
            } else if (Value == 3) {
                MT.hs100 = false;
                MT.hs70 = false;
                MT.aimBody = !MT.aimBody;
                MT.aimBody = true;
                LOGI("hs100.hs70.aimBody.aimBody");

            }
            break;

        case 2:
            MT.aimFire= !MT.aimFire;
            LOGD("aimFire");
            break;

        case 3:
            MT.aimScope= !MT.aimScope;
            break;

        case 4:
            MT.aimAgachado = !MT.aimAgachado;
            break;

        case 5:
            if (Value > 0) {
                MT.Fov_Aim = 1.0f - (0.0020f * (float)Value);
            }
            break;

        case 6:
            if (Value > 0) {
                MT.aimBotFov = 1.0f - (0.0020f * (float)Value);
            }
            break;

        case 7:
            if (Value == 0) {
                hexlibPatches.SensibilidadBaja.Restore();
            } else if (Value == 1) {
                hexlibPatches.SensibilidadBaja.Modify();
            } else if (Value == 2) {
                hexlibPatches.SensibilidadMedia.Modify();
            } else if (Value == 3) {
                hexlibPatches.SensibilidadAlta.Modify();
            }
            break;

        case 8:
            MT.espFire = !MT.espFire;
            break;

        case 9:
            MT.espNames = !MT.espNames;
            break;

        case 10:
            MT.AlertWorld = !MT.AlertWorld;
            break;

        case 11:
            MT.AlertAround = !MT.AlertAround;
            break;

        case 12:
            if (Value == 0) {
                hexlibPatches.VelocidadDeDisparo1.Restore();
            } else if (Value == 1) {
                hexlibPatches.VelocidadDeDisparo1.Modify();
            } else if (Value == 2) {
                hexlibPatches.VelocidadDeDisparo2.Modify();
            } else if (Value == 3) {
                hexlibPatches.VelocidadDeDisparo3.Modify();
            }
            break;

        case 13:
            if (Value == 0) {
                hexlibPatches.LluviaDeBalas1.Restore();
            } else if (Value == 1) {
                hexlibPatches.LluviaDeBalas1.Modify();
            } else if (Value == 2) {
                hexlibPatches.LluviaDeBalas2.Modify();
            } else if (Value == 3) {
                hexlibPatches.LluviaDeBalas3.Modify();
            } else if (Value == 4) {
                hexlibPatches.LluviaDeBalas4.Modify();
            } else if (Value == 5) {
                hexlibPatches.LluviaDeBalas5.Modify();
            } else if (Value == 6) {
                hexlibPatches.LluviaDeBalas6.Modify();
            } else if (Value == 7) {
                hexlibPatches.LluviaDeBalas7.Modify();
            } else if (Value == 8) {
                hexlibPatches.LluviaDeBalas8.Modify();
            } else if (Value == 9) {
                hexlibPatches.LluviaDeBalas9.Modify();
            } else if (Value == 10) {
                hexlibPatches.LluviaDeBalas10.Modify();
            } else if (Value == 11) {
                hexlibPatches.LluviaDeBalas11.Modify();
            } else if (Value == 12) {
                hexlibPatches.LluviaDeBalas12.Modify();
            } else if (Value == 13) {
                hexlibPatches.LluviaDeBalas13.Modify();
            } else if (Value == 14) {
                hexlibPatches.LluviaDeBalas14.Modify();
            } else if (Value == 15) {
                hexlibPatches.LluviaDeBalas15.Modify();
            } else if (Value == 16) {
                hexlibPatches.LluviaDeBalas16.Modify();
            } else if (Value == 17) {
                hexlibPatches.LluviaDeBalas17.Modify();
            } else if (Value == 18) {
                hexlibPatches.LluviaDeBalas18.Modify();
            } else if (Value == 19) {
                hexlibPatches.LluviaDeBalas19.Modify();
            } else if (Value == 20) {
                hexlibPatches.LluviaDeBalas20.Modify();
            }
            break;

        case 14:
            MT.teleKill = !MT.teleKill;
            MT.ghost = !MT.ghost;
            break;

        case 15:
            KMHack2 = !KMHack2;
            if (KMHack2) {
                hexlibPatches.ModoFantasma.Modify();
            } else {
                hexlibPatches.ModoFantasma.Restore();
            }
            break;


        case 16:
            if (Value == 0) {
                hexlibPatches.Speed.Restore();
            } else if (Value == 1) {
                hexlibPatches.Speed2x.Modify();
            } else if (Value == 2) {
                hexlibPatches.Speed3x.Modify();
            } else if (Value == 3) {
                hexlibPatches.Speed4x.Modify();
            } else if (Value == 4) {
                hexlibPatches.Speed5x.Modify();
            } else if (Value == 5) {
                hexlibPatches.Speed5x.Modify();
            }
            break;

        case 17:
            if (Value == 0) {
                hexlibPatches.ModificarCuerpoDeEnemigos1.Restore();
            } else if (Value == 1) {
                hexlibPatches.ModificarCuerpoDeEnemigos1.Modify();
            } else if (Value == 2) {
                hexlibPatches.ModificarCuerpoDeEnemigos2.Modify();
            } else if (Value == 3) {
                hexlibPatches.ModificarCuerpoDeEnemigos3.Modify();
            }
            break;

        case 18:
            KMHack3 = !KMHack3;
            if (KMHack3) {
                hexlibPatches.MunicionesIlimitadas.Modify();
            } else {
                hexlibPatches.MunicionesIlimitadas.Restore();
            }
            break;

        case 19:
            KMHack4 = !KMHack4;
            if (KMHack4) {
                hexlibPatches.RecargaRapida.Modify();
            } else {
                hexlibPatches.RecargaRapida.Restore();
            }
            break;

        case 20:
            KMHack5 = !KMHack5;
            if (KMHack5) {
                hexlibPatches.SilenciarDisparos.Modify();
            } else {
                hexlibPatches.SilenciarDisparos.Restore();
            }
            break;



        case 21:
            KMHack6 = !KMHack6;
            if (KMHack6) {
                hexlibPatches.DisparosEnMovimiento.Modify();
            } else {
                hexlibPatches.DisparosEnMovimiento.Restore();
            }
            break;


        case 22:
            KMHack7 = !KMHack7;
            if (KMHack7) {
                hexlibPatches.DisparosAutomaticos.Modify();
            } else {
                hexlibPatches.DisparosAutomaticos.Restore();
            }
            break;



        case 23:
            if (Value == 0) {
                hexlibPatches.AmpliarVista1.Restore();
            } else if (Value == 1) {
                hexlibPatches.AmpliarVista1.Modify();
            } else if (Value == 2) {
                hexlibPatches.AmpliarVista2.Modify();
            } else if (Value == 3) {
                hexlibPatches.AmpliarVista3.Modify();
            } else if (Value == 4) {
                hexlibPatches.AmpliarVista4.Modify();
            } else if (Value == 5) {
                hexlibPatches.AmpliarVista5.Modify();
            } else if (Value == 6) {
                hexlibPatches.AmpliarVista6.Modify();
            }
            break;


        case 24:
            MT.fakeName = !MT.fakeName;
            break;

        case 25:
            KMHack8 = !KMHack8;
            if (KMHack8) {
                hexlibPatches.ModoNoche.Modify();
            } else {
                hexlibPatches.ModoNoche.Restore();
            }
            break;

        case 26:
            KMHack9 = !KMHack9;
            if (KMHack9) {
                hexlibPatches.ModoFullHd.Modify();;
            } else {
                hexlibPatches.ModoFullHd.Restore();
            }
            break;

        case 27:
            KMHack10 = !KMHack10;
            if (KMHack10) {
                hexlibPatches.MedikitCorriendo1.Modify();
                hexlibPatches.MedikitCorriendo2.Modify();
            } else {
                hexlibPatches.MedikitCorriendo1.Restore();
                hexlibPatches.MedikitCorriendo2.Restore();
            }
            break;

        case 28:
            KMHack11 = !KMHack11;
            if (KMHack11) {
                hexlibPatches.CarroTranspasaParedes1.Modify();
                hexlibPatches.CarroTranspasaParedes2.Modify();
            } else {
                hexlibPatches.CarroTranspasaParedes1.Restore();
                hexlibPatches.CarroTranspasaParedes2.Restore();
            }
            break;

        case 29:
            MT.Gravity = !MT.Gravity;
            break;

        case 30:
            KMHack12 = !KMHack12;
            if (KMHack12) {
                hexlibPatches.MatarATodosEnElLobby.Modify();
            } else {
                hexlibPatches.MatarATodosEnElLobby.Restore();
            }
            break;

        case 31:
            KMHack13 = !KMHack13;
            if (KMHack13) {
                hexlibPatches.speedx250.Modify();
            } else {
                hexlibPatches.speedx250.Restore();
            }
            break;

        case 32:
            KMHack14 = !KMHack14;
            if (KMHack14) {
                hexlibPatches.FlyCarro.Modify();
            } else {
                hexlibPatches.FlyCarro.Restore();
            }
            break;

        case 33:
            KMHack15 = !KMHack15;
            if (KMHack15) {
                hexlibPatches.TeleportCarro.Modify();
            } else {
                hexlibPatches.TeleportCarro.Restore();
            }
            break;

        case 34:
            KMHack16 = !KMHack16;
            if (KMHack16) {
                hexlibPatches.ZePedrinha.Modify();
            } else {
                hexlibPatches.ZePedrinha.Restore();
            }
            break;

        case 35:
            KMHack17 = !KMHack17;
            if (KMHack17) {
                hexlibPatches.WallCarro.Modify();
            } else {
                hexlibPatches.WallCarro.Restore();
            }
            break;

        case 36:
            if (Value == 0) {
                hexlibPatches.Underground1.Restore();
            } else if (Value == 1) {
                hexlibPatches.Underground1.Modify();
            } else if (Value == 2) {
                hexlibPatches.Underground2.Modify();
            }
            break;

        case 37:
            MT.AntLogs= !MT.AntLogs;
            break;
    }
}


void (*LateUpdate)(void *componentPlayer);
void AimBot(void *local_player, void *enemy_player) {

    int pose = GetPhysXPose(enemy_player);
    bool alive = get_isAlive(enemy_player);
    bool visible = get_isVisible(enemy_player);
    bool visi = get_AttackableEntity_IsVisible(enemy_player);
    bool visir = get_AttackableEntity_GetIsDead(enemy_player);

    bool sameteam = get_isLocalTeam(enemy_player);
    void *HeadTF = *(void **)((uintptr_t)enemy_player + Global.HeadTF);
    void *HipTF = *(void **)((uintptr_t)enemy_player + Global.HipTF);
    void *Main_Camera = *(void **)((uintptr_t)local_player + Global.MainCameraTransform);

    if (alive && pose != 8  && visible && !sameteam && HeadTF != NULL && Main_Camera != NULL && HipTF != NULL) {
        Vector3 EnemyLocation = Transform_INTERNAL_GetPosition(HeadTF);
        Vector3 CenterWS = GetAttackableCenterWS(local_player);
        bool scope = get_IsSighting(local_player);
        bool agachado = get_IsCrouching(local_player);
        float distance = Vector3::Distance(CenterWS, EnemyLocation);

        Vector3 PlayerLocation = Transform_INTERNAL_GetPosition(Main_Camera);
        Quaternion PlayerLook = GetRotationToLocation(EnemyLocation, 0.1f, PlayerLocation);
        Quaternion PlayerLook2 = GetRotationToLocation(Transform_INTERNAL_GetPosition(HipTF), 0.1f, PlayerLocation);
        Vector3 fwd = GetForward(Main_Camera);

        Vector3 nrml = Vector3::Normalized(EnemyLocation - PlayerLocation);
        float PlayerDot = Vector3::Dot(fwd, nrml);

        if (MT.espNear) {
            for (int u = 0; u < 50; u++) {
                monoString *alert = FormatCount(MT.enemyCountWorld, MT.botCountWorld);
                if (alert != NULL) {
                    ShowDynamicPopupMessage(alert);
                }
            }
        }
        bool isEspRead = false;

        if (!isEspRead) {
            int tmpEnemyCountWorld = 0;
            int tmpBotCountWorld = 0;
            int tmpEnemyCountAround = 0;
            int tmpBotCountAround = 0;
            if (enemy_player != NULL && enemy_player != local_player) {
                bool isBot = *(bool*)((uintptr_t)enemy_player + 0xC4);
                if (isBot) {
                    ++tmpBotCountWorld;
                } else {
                    ++tmpEnemyCountWorld;

                }

            }

            isEspRead = true;
            MT.enemyCountWorld = tmpEnemyCountWorld;
            MT.botCountWorld = tmpBotCountWorld;
            MT.enemyCountAround = tmpEnemyCountAround;
            MT.botCountAround = tmpBotCountAround;
        }
        if (MT.AlertWorld) {
            monoString *alert = FormatCount(MT.enemyCountWorld, MT.botCountWorld);
            if (alert != NULL) {
                ShowDynamicPopupMessage(alert);
            }
        }


        if (MT.DISTANCECENTER) {
            monoString *distances = U3DStrFormat(distance);
            if (distances != NULL) {
                ShowPopupMessages(distances);
            }
        }

        if (MT.espFire) {
            void *imo = get_imo(local_player);
            if (imo != NULL && distance > 1.0f) {
                set_esp(imo, CenterWS, EnemyLocation);
            }
        }


        if (MT.fakeName) {
            spofNick(local_player);
        }

        if (MT.espNames) {
            void *ui = CurrentUIScene();
            if (ui != NULL) {
                monoString *nick = get_NickName(enemy_player);
                monoString *distances = U3DStrFormat(distance);
                AddTeammateHud(ui, nick, distances);
            }
        }
        if (MT.fakeName) {
            spofNick(local_player);
        }


        if (MT.teleKill) {
            set_aim(local_player, PlayerLook);
            void *_MountTF = Component_GetTransform(enemy_player);
            if (_MountTF != NULL) {
                Vector3 MountTF =
                        Transform_INTERNAL_GetPosition(_MountTF) - (GetForward(_MountTF) * 1.6f);
                Transform_INTERNAL_SetPosition(Component_GetTransform(local_player), Vvector3(MountTF.X, MountTF.Y, MountTF.Z));
            }
        }


        if ((agachado && MT.aimAgachado) && ((PlayerDot > 0.998f && !MT.aimBotFov) || (PlayerDot > MT.Fov_Aim && MT.aimBotFov))) {

            set_aim(local_player, PlayerLook);
        }


        if ((scope && MT.aimScope) && ((PlayerDot > 0.998f && !MT.aimBotFov) || (PlayerDot > MT.Fov_Aim && MT.aimBotFov))) {
            set_aim(local_player, PlayerLook);

        }


        bool firing = IsFiring(local_player);
        if ((firing && MT.aimFire) && ((PlayerDot > 0.998f && !MT.aimBotFov) || (PlayerDot > MT.Fov_Aim && MT.aimBotFov))) {


            if (MT.aimBody) {
                set_aim(local_player, PlayerLook2);
            }
            if (MT.hs100) {
                set_aim(local_player, PlayerLook);
            }
            if (MT.hs70) {
                if (MT.aimbotauto)
                {
                    set_aim(local_player, PlayerLook);
                    ++MT.semihs;
                } else {
                    set_aim(local_player, PlayerLook2);
                    --MT.semihs;
                }

                if (MT.semihs == 6)
                {
                    MT.aimbotauto = false;
                } else if (MT.semihs == 0) {
                    MT.aimbotauto = true;
                }
                if (MT.semihs > 6 || MT.semihs < 0)
                {
                    MT.semihs = 3;
                    MT.aimbotauto = true;
                }
            }
        }
    }
}

bool isEspReady = false;

void *fakeEnemy;
void _LateUpdate(void *player){
    if (player != NULL) {
        void *local_player = Current_Local_Player();
        if (local_player == NULL){
            local_player = GetLocalPlayerOrObServer();
        }
        if (local_player != NULL){
            void *current_match = Curent_Match();
            if (current_match != NULL) {
                void *fakeCamPlayer = get_MyFollowCamera(local_player);
                void *fakeCamEnemy = get_MyFollowCamera(player);
                if (fakeCamPlayer != NULL && fakeCamEnemy != NULL){
                    void *fakeCamPlayerTF = Component_GetTransform(fakeCamPlayer);
                    void *fakeCamEnemyTF = Component_GetTransform(player);
                    if (fakeCamPlayerTF != NULL && fakeCamEnemyTF != NULL){
                        Vector3 fakeCamPlayerPos = Transform_INTERNAL_GetPosition(fakeCamPlayerTF);
                        Vector3 fakeCamEnemyPos = Transform_INTERNAL_GetPosition(fakeCamEnemyTF);
                        float distance = Vector3::Distance(fakeCamPlayerPos, fakeCamEnemyPos);
                        if (player != local_player){
                            if (distance > 1.6f) {
                                bool sameteams = get_isLocalTeam(player);
                                int pose = GetPhysXPose(player);
                                bool alive = get_isAlive(player);
                                bool visible = get_isVisible(player);
                                bool visir = get_AttackableEntity_GetIsDead(player);

                                if (!sameteams && pose != 8 && alive && visible){
                                    AimBot(local_player, player);
                                }
                            } else {
                                fakeEnemy = player;
                            }
                        }
                    }

                }
            }
        }
    }
    LateUpdate(player);
}

bool (*orig_ghost)(void* _this, int value);
bool _ghost(void* _this, int value){
    if (_this != NULL){
        if (MT.ghost || MT.teleKill){
            return false;
        }
    }
    return orig_ghost(_this, value);
}


bool(*initializeRank)(void* _this);
bool _InitializeRank(void* _this) {
    return true;
}

bool(*acharpartida)(void* _this);
bool _acharpartida(void* _this){
    return false;
}

bool(*imei)(void* _this);
bool _imei(void* _this){
    return false;
}

void(*acharpartida0)(void* _this);
void _acharpartida0(void* _this){

}

void(*acharpartida3)(void* _this);
void _acharpartida3(void* _this){

}

bool (*GravityTrue)(void* _this);
bool _GravityTrue(void* _this) {
    if (MT.Gravity) {
        return true;
    }
    return GravityTrue(_this);
}


float (*NegativeGravity)(int* _this);
float _NegativeGravity(int* _this) {
    if (NegativeGravity != NULL) {
        if (MT.Gravity) {
            return -10.0f;
        }
    }
    return NegativeGravity(_this);
}

void (*antLogs)(void *_this);
void _antLogs(void *_this) {
    if (MT.AntLogs) {

    }
    return antLogs(_this);
}
// we will run our hacks in a new thread so our while loop doesn't block process main thread
void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName1));
    //Anti-lib rename
    /*
    do {
        sleep(1);
    } while (!isLibraryLoaded("libYOURNAME.so"));*/

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);
    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName1);

#if defined(__aarch64__) //To compile this code for arm64 lib only. Do not worry about greyed out highlighting code, it still works


#else //To compile this code for armv7 lib only.

    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!


    // Patching offsets directly. Strings are automatically obfuscated too!
    //PATCHES
    //Lluvia De Balas//
    hexlibPatches.ZePedrinha = MemoryPatch(targetLibName1, 0xEF2B60, "\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF", 16);
    hexlibPatches.WallCarro = MemoryPatch(targetLibName, 0x21D1ED4, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speedcarro1 = MemoryPatch(targetLibName, 0xACBB5C , "\x8A\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speedcarro2 = MemoryPatch(targetLibName, 0xACBB5C , "\x8D\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speedcarro3 = MemoryPatch(targetLibName, 0xACBB5C , "\x96\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speedcarro4 = MemoryPatch(targetLibName,11373644 , "\x98\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speedcarro5 = MemoryPatch(targetLibName,11373644 , "\x99\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Underground1 = MemoryPatch(targetLibName, 0x2757518, "\x00\x40\x1C\x45", 4);
    hexlibPatches.Underground2 = MemoryPatch(targetLibName, 42162532, "\x00\x40\x1C\x45", 4);
    hexlibPatches.speedx250 = MemoryPatch(targetLibName, 0xA7C730, "\xFA\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speed = MemoryPatch(targetLibName ,0xA7C730 , "\x82\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speed2x = MemoryPatch(targetLibName, 0xA7C730 , "\x83\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speed3x = MemoryPatch(targetLibName, 0xA7C730 , "\x84\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speed4x = MemoryPatch(targetLibName, 0xA7C730 , "\x85\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.Speed5x = MemoryPatch(targetLibName, 0xA7C730 , "\x82\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.TeleportCarro = MemoryPatch(targetLibName, 0x2786DE0, "\x58\x10\x1C\x45", 4);
    hexlibPatches.FlyCarro = MemoryPatch(targetLibName, 0x2786EF8, "\x58\x10\x1C\x45", 4);
    hexlibPatches.LluviaDeBalas1 = MemoryPatch(targetLibName, 0xC75ADC, "\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas2 = MemoryPatch(targetLibName, 0xC75ADC, "\x02\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas3 = MemoryPatch(targetLibName, 0xC75ADC, "\x03\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas4 = MemoryPatch(targetLibName, 0xC75ADC, "\x04\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas5 = MemoryPatch(targetLibName, 0xC75ADC, "\x05\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas6 = MemoryPatch(targetLibName, 0xC75ADC, "\x06\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas7 = MemoryPatch(targetLibName, 0xC75ADC, "\x07\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas8 = MemoryPatch(targetLibName, 0xC75ADC, "\x08\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas9 = MemoryPatch(targetLibName, 0xC75ADC, "\x9\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas10 = MemoryPatch(targetLibName, 0xC75ADC, "\x10\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas11 = MemoryPatch(targetLibName, 0xC75ADC, "\x11\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas12 = MemoryPatch(targetLibName, 0xC75ADC, "\x12\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas13 = MemoryPatch(targetLibName, 0xC75ADC, "\x13\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas14 = MemoryPatch(targetLibName, 0xC75ADC, "\x14\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas15 = MemoryPatch(targetLibName, 0xC75ADC, "\x15\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas16 = MemoryPatch(targetLibName, 0xC75ADC, "\x16\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas17 = MemoryPatch(targetLibName, 0xC75ADC, "\x17\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas18 = MemoryPatch(targetLibName, 0xC75ADC, "\x18\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas19 = MemoryPatch(targetLibName, 0xC75ADC, "\x19\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.LluviaDeBalas20 = MemoryPatch(targetLibName, 0xC75ADC, "\x20\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Silenciar Dispaross//
    hexlibPatches.SilenciarDisparos = MemoryPatch(targetLibName, 0xC82640, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Remover Miras//
    hexlibPatches.RemoverMiras = MemoryPatch(targetLibName, 0xB979E8, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Municiones Ilimitadas//
    hexlibPatches.MunicionesIlimitadas = MemoryPatch(targetLibName, 0x179EF04, "\x03\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Velocidad De Disparo//
    hexlibPatches.VelocidadDeDisparo1 = MemoryPatch(targetLibName, 0xC75A5C, "\x02\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.VelocidadDeDisparo2 = MemoryPatch(targetLibName, 0xC75A5C, "\x03\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.VelocidadDeDisparo3 = MemoryPatch(targetLibName, 0xC75A5C, "\x04\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Recarga Rapida//
    hexlibPatches.RecargaRapida = MemoryPatch(targetLibName, 0xC75C30, "\x12\x03\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Cambio Rapido De Arma//
    hexlibPatches.CambioRapidoDeArma = MemoryPatch(targetLibName, 0xB9F2D0, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Reducir Lag//
    hexlibPatches.ReducirLag = MemoryPatch(targetLibName, 0xC849F8, "\x12\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Disparo En Movimiento//
    hexlibPatches.DisparosEnMovimiento = MemoryPatch(targetLibName, 0xB8F7B4, "\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Disparos Automaticos//
    hexlibPatches.DisparosAutomaticos = MemoryPatch(targetLibName, 0xC7547C, "\x02\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Teletransportar Carro// falta codigo
    hexlibPatches.TeletransportarCarro1 = MemoryPatch(targetLibName, 0x2786DE0, "\x58\x10\x1C\x45", 4);
    hexlibPatches.TeletransportarCarro2 = MemoryPatch(targetLibName, 0x2786EF8, "\x58\x10\x1C\x45", 4);
//Matar a Todos En El Lobby//
    hexlibPatches.MatarATodosEnElLobby = MemoryPatch(targetLibName, 0xC63B18, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Modo Fantasma//
    hexlibPatches.ModoFantasma = MemoryPatch(targetLibName, 0x1B8ACCC, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Fantasma Veloz// falta codigo
    hexlibPatches.FantasmaVeloz1 = MemoryPatch(targetLibName, 0x1B8ACCC, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.FantasmaVeloz2 = MemoryPatch(targetLibName, 0xA7C730, "\x96\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
//Velocidad De Correr// falta codigo
    hexlibPatches.VelocidadDeCorrer1 = MemoryPatch(targetLibName, 0x179ED24, "\x81\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.VelocidadDeCorrer2 = MemoryPatch(targetLibName, 0x179ED24, "\x82\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.VelocidadDeCorrer3 = MemoryPatch(targetLibName, 0x179ED24, "\x83\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.VelocidadDeCorrer4 = MemoryPatch(targetLibName, 0x179ED24, "\x84\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.VelocidadDeCorrer5 = MemoryPatch(targetLibName, 0x179ED24, "\x85\x0F\x43\xE3\x1E\xFF\x2F\xE1", 8);
//Cuerpos Blancos//
    hexlibPatches.CuerposBlancos1 = MemoryPatch(targetLibName, 0xB6BCA0, "\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.CuerposBlancos2 = MemoryPatch(targetLibName, 0x188BBE0, "\x00\x00\xBB\xE3\x1E\xFF\x2F\xE1", 8);
//Sensibilidad Personaje// falta codigo
    hexlibPatches.SensibilidadBaja = MemoryPatch(targetLibName, 0xA7D378, "\x00\x00\x48\x43", 4);
    hexlibPatches.SensibilidadMedia = MemoryPatch(targetLibName, 0xA7D378, "\x00\x00\x16\x43", 4);
    hexlibPatches.SensibilidadAlta = MemoryPatch(targetLibName, 0xA7D378, "\x00\x00\x96\x42", 4);
//En Primera Persona//
    hexlibPatches.EnPrimeraPersona = MemoryPatch(targetLibName, 0xC700D0, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Medikit Corriendo//
    hexlibPatches.MedikitCorriendo1 = MemoryPatch(targetLibName, 0xB8929C, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.MedikitCorriendo2 = MemoryPatch(targetLibName, 0x22F55A8, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Carro Transpasa Paredes// falta codigo
    hexlibPatches.CarroTranspasaParedes1 = MemoryPatch(targetLibName, 0x28F0444, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.CarroTranspasaParedes2 = MemoryPatch(targetLibName, 0x2C934C4, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Eliminar Arboles// falta codigo
    hexlibPatches.EliminarArboles = MemoryPatch(targetLibName, 0x19BF338, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Eliminar Grama// falta codigo
    hexlibPatches.ElimimarGrama = MemoryPatch(targetLibName, 0x19BF850, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Mapa Full HD//
    hexlibPatches.ModoFullHd = MemoryPatch(targetLibName, 0x2AAFBE8, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Ampliar Vista//
    hexlibPatches.AmpliarVista1 = MemoryPatch(targetLibName, 0xC700D0, "\x32\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.AmpliarVista2 = MemoryPatch(targetLibName, 0xC700D0, "\x64\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.AmpliarVista3 = MemoryPatch(targetLibName, 0xC700D0, "\x7F\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.AmpliarVista4 = MemoryPatch(targetLibName, 0xC700D0, "\xC8\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.AmpliarVista5 = MemoryPatch(targetLibName, 0xC700D0, "\xFA\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    hexlibPatches.AmpliarVista6 = MemoryPatch(targetLibName, 0xC700D0, "\x2C\x01\x44\xE3\x1E\xFF\x2F\xE1", 8);
//Caer En 360//
    hexlibPatches.CaerEn360 = MemoryPatch(targetLibName, 0x1A7B764, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Diamantes Infinitos//
    hexlibPatches.DiamantesInfinitos = MemoryPatch(targetLibName, 0x18A2A9C, "\xEF\x05\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Oro Infinito//
    hexlibPatches.OroInfinito = MemoryPatch(targetLibName, 0x18A2A8C, "\xEF\x05\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Likes Infinitos//
    hexlibPatches.LikesInfinitos = MemoryPatch(targetLibName, 0x29A46B4, "\xEF\x05\xA0\xE3\x1E\xFF\x2F\xE1", 8);
//Ser Heroico//
    hexlibPatches.SerHeroico = MemoryPatch(targetLibName, 0x29A4644, "\x13\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);

    MSHookFunction((void*)getRealOffset(0xB89958), (void*)_LateUpdate, (void**)&LateUpdate);

    HOOK(0xA9F550, _GravityTrue, GravityTrue);
    HOOK(0xA42BD4, _NegativeGravity, NegativeGravity);
    //Ranked
    HOOK(0x2A5B1C0, _InitializeRank, initializeRank);

    //Sistema Ranked
    MSHookFunction((void*)getRealOffset(0x16DDD10), (void*)_acharpartida, (void**)&acharpartida);
    MSHookFunction((void*)getRealOffset(0x16E2DA4), (void*)_acharpartida, (void**)&acharpartida);
    MSHookFunction((void*)getRealOffset(0x16E3DDC), (void*)_acharpartida, (void**)&acharpartida);
    MSHookFunction((void*)getRealOffset(0x270F7B4), (void*)_acharpartida, (void**)&acharpartida);
    MSHookFunction((void*)getRealOffset(0x2A3DDF4), (void*)_acharpartida0, (void**)&acharpartida0);
    MSHookFunction((void*)getRealOffset(0xFA3C68), (void*)_acharpartida0, (void**)&acharpartida0);
    MSHookFunction((void*)getRealOffset(0x2A59E64), (void*)_acharpartida3, (void**)&acharpartida3);
    MSHookFunction((void*)getRealOffset(0xFAC28C), (void*)_acharpartida3, (void**)&acharpartida3);

    //ghost do telekil
    HOOK(0x1B8ACCC, _ghost, orig_ghost);
    HOOK(0xB53204, _NegativeGravity, NegativeGravity);
    HOOK(0xBB30FC, _GravityTrue, GravityTrue);
    LOGI(OBFUSCATE("Done"));
    return NULL;
#endif

    //Anti-leech
    /*if (!iconValid || !initValid || !settingsValid) {
        //Bad function to make it crash
        sleep(5);
        int *p = 0;
        *p = 0;
    }*/

    return NULL;
}
void *Super_thread(void *) {
    LOGD("Carregando...");

    ProcMap unityMap;
    do {
        unityMap = KittyMemory::getLibraryMap(targetLibName1);
        sleep(1);
    } while (!unityMap.isValid());

    //Mapa Modo Noche//
    hexlibPatches.ModoNoche = MemoryPatch(targetLibName1, 0x1A2290, "\x00\x00\x80\xBF", 4);
//Mapa Negro//
    hexlibPatches.MapaNegro = MemoryPatch(targetLibName1, 0x19ECE4, "\xF0\x23\x73\xC9", 4);
//Mapa Negro//
    hexlibPatches.MapaBlanco = MemoryPatch(targetLibName1, 0x19ECE4, "\x00\xC0\x79\x44", 4);
//Modificar Cuerpo De Enemigos//
    hexlibPatches.ModificarCuerpoDeEnemigos1 = MemoryPatch(targetLibName1, 0x29BC38, "\x00\x00\xC8\x30", 4);
    hexlibPatches.ModificarCuerpoDeEnemigos2 = MemoryPatch(targetLibName1, 0x29BC38, "\x00\x00\xC8\x40", 4);
    hexlibPatches.ModificarCuerpoDeEnemigos3 = MemoryPatch(targetLibName1, 0x29BC38, "\x00\x00\xC8\x41", 4);
//Transpasar Piedras//
    hexlibPatches.TranspasarPiedras = MemoryPatch(targetLibName1, 0xEF2B60, "\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF", 16);
    return NULL;
}















__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("hkg/android/hackudogamer/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("hkg/android/hackudogamer/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("hkg/android/hackudogamer/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);

    if (RegisterMenu(env) != 0)
       return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}

