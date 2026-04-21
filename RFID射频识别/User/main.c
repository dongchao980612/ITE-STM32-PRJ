#include "stm32f10x.h"
#include "oled.h"
#include "rc522.h"
#include "delay.h"

// ===================== 物品列表（英文名称） =====================
typedef struct
{
    uint8_t uid[4];
    char name[16];
} Item_Typedef;

Item_Typedef Item_List[] =
{
    {{0x77, 0x0F, 0x43, 0x63}, "MY_CARD"}
};

#define ITEM_COUNT (sizeof(Item_List)/sizeof(Item_Typedef))

// ===================== 仓库数据 =====================
#define MAX_CARD 10
uint8_t warehouse[MAX_CARD][4];
uint8_t in_flag[MAX_CARD] = {0};

// ===================== 工具函数 =====================
uint8_t Card_Cmp(uint8_t *a, uint8_t *b)
{
    for (uint8_t i = 0; i < 4; i++)
        if (a[i] != b[i])
        {
            return 0;
        }

    return 1;
}

int8_t Find_Card(uint8_t *id)
{
    for (uint8_t i = 0; i < MAX_CARD; i++)
        if (in_flag[i] && Card_Cmp(warehouse[i], id))
        {
            return i;
        }

    return -1;
}

void Add_Card(uint8_t *id)
{
    for (uint8_t i = 0; i < MAX_CARD; i++)
    {
        if (!in_flag[i])
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                warehouse[i][j] = id[j];
            }

            in_flag[i] = 1;
            break;
        }
    }
}

void Remove_Card(uint8_t *id)
{
    int8_t idx = Find_Card(id);

    if (idx >= 0)
    {
        in_flag[idx] = 0;
    }
}

uint8_t Get_Count(void)
{
    uint8_t cnt = 0;

    for (uint8_t i = 0; i < MAX_CARD; i++) if (in_flag[i])
        {
            cnt++;
        }

    return cnt;
}

char* Get_Item_Name(uint8_t *uid)
{
    for (uint8_t i = 0; i < ITEM_COUNT; i++)
    {
        if (Card_Cmp(uid, Item_List[i].uid))
        {
            return Item_List[i].name;
        }
    }

    return "UNKNOWN";
}

// ===================== 显示标题 =====================
void Show_Title(void)
{
    OLED_ShowString(1, 1, "=== WAREHOUSE ===");
}

// ===================== 主函数 =====================
int main(void) {
    OLED_Init();
    RC522_Init();
    Show_Title();

    uint8_t type[2];
    uint8_t card_id[4];
    uint8_t sta;
    char *name;

    while (1) {
        sta = RC522_Request(0x26, type);

        if (sta == MI_OK) {
            if (RC522_Anticoll(card_id) == MI_OK) {
                name = Get_Item_Name(card_id);

                // 显示物品名称
                OLED_ShowString(3, 1, "Item: ");
                OLED_ShowString(3, 7, name);

                // 显示UID
                OLED_ShowHexNum(4, 1, card_id[0], 2);
                OLED_ShowHexNum(4, 3, card_id[1], 2);
                OLED_ShowHexNum(4, 5, card_id[2], 2);
                OLED_ShowHexNum(4, 7, card_id[3], 2);

                // 进出库判断
                if (Find_Card(card_id) >= 0) {
                    OLED_ShowString(2, 1, "Status: OUT    ");
                    Remove_Card(card_id);
                } else {
                    OLED_ShowString(2, 1, "Status: IN     ");
                    Add_Card(card_id);
                }

                // 显示库存数量
                OLED_ShowString(4, 10, "CNT:");
                OLED_ShowNum(4, 14, Get_Count(), 1);

                Delay_ms(600);
            }
        } else {
            // 无卡状态
            OLED_ShowString(2, 1, "Status: WAIT...");
            OLED_ShowString(3, 1, "                ");
            OLED_ShowString(4, 1, "                ");
        }

        RC522_Halt();
        Delay_ms(150);
    }
}
