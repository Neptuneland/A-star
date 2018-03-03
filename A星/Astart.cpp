#include "stdafx.h"
#include "Astart.h"
//=====�Ż�����==================================================================================






//CAstar::PVIR_INFO CAstar::m_pVir;





//=====�Ż�����==================================================================================

CAstar::CAstar()
{
}


CAstar::~CAstar()
{
}

void CAstar::InitMapInfo(int* pMap, int nHigh, int nWidth, int nBlock)
{
	m_pMap     = pMap;
	m_MapHigh  = nHigh;
	m_MapWidth = nWidth;
	m_Block    = nBlock;
//=====�Ż�����==================================================================================






	//m_pVir = new VIR_INFO[m_MapHigh*m_MapWidth]{};






//=====�Ż�����==================================================================================

	m_bInitMapInfo = true;
}

void CAstar::InitCoord(COORD codStar, COORD codEnd)
{
	m_Start = codStar;
	m_End   = codEnd;
	m_bInitCoordInfo = true;
}

bool CAstar::FindPath()
{
	//�Ƿ��ʼ�����
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
/*
   1.  ��������걣�浽Open����
   2.1 �ж�Open���Ƿ�Ϊ�գ�����˵����·��ͬ
   2.2 �ҳ�Open����Fֵ��С�ĵ�
   2.3 ������ɢ
   2.4 ����ɢ�ĵ㱣�浽Close���У���Open����ɾ��
   2.5 �ж�����ɢ�����ĵ��Ƿ�ϸ�
      2.5.1 �Ƿ����յ㣬�Ǿ�ֱ�ӷ���
	        �ǲ����ϰ���
			�ǲ���Խ��
			�Ƿ���Open����
			�Ƿ���Close����
   2.6 �Ѻϸ�ĵ���Open����
   2.7 �ظ�2.1 -- 2.6
*/

	//���Open��Close��
	m_Open.clear();
	m_Close.clear();

	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//��ʼѭ������

	while (true)
	{
		//Open���Ƿ�Ϊ��
		if (m_Open.empty())
		{
			return false;
		}
		//��Open����Fֵ��С�ĵ�
		int nIndex = 0;
		for (int i = 1; i < m_Open.size();i++)
		{
			//�����ǰ��nIndex���� i�� ����
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}

		//����������С�ĵ���ɢ
		//��ɢ
		NODE_INFO nodeNew[4]{ };

		//��
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//��
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;
		//��
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y ;
		//��
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y;

		for (int i = 0; i < 4;i++)
		{
			nodeNew[i].codParent = m_Open[nIndex].codSelf;
			nodeNew[i].g = m_Open[nIndex].g + 1;
			nodeNew[i].SetH_F(nodeNew[i].codSelf, m_End);
			//����
			nodeNew[i].codSelf.d = i;
		}
//=====�Ż�����==================================================================================



		//int x1 = m_Open[nIndex].codSelf.X;
		//int y1 = m_Open[nIndex].codSelf.Y;
		//m_pVir[y1 * m_MapWidth + x1].isClose = true;
		//m_pVir[y1 * m_MapWidth + x1].isOpen  = false;




//=====�Ż�����==================================================================================

		//����ɢ���ĵ㱣�浽Close������Open����ɾ��
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//�����ɢ�����ĵ��Ƿ�ϸ��Ƿ����յ�
		for (int i = 0; i < 4;i++)
		{
			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//�ǲ����յ�
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}
			//�Ƿ�Խ��
			if (x <= 0 || y <= 0 ||
				x >= m_MapWidth  ||
				y >= m_MapHigh)
			{
				continue;
			}
			//�Ƿ����ϰ���
			if (m_pMap[y*m_MapWidth + x] == m_Block)
			{
				continue;
			}

//=====�Ż�����==================================================================================




			////�ж��Ƿ���Open���Close����
			//if (m_pVir[y * m_MapWidth + x].isClose ||
			//	m_pVir[y * m_MapWidth + x].isOpen)
			//{
			//	continue;
			//}

//=====�Ż�����==================================================================================


			//�Ƿ���Open����
			
			
//=====û���Ż�����===========================================================================
 			bool bRet = false;
 			for (int o = 0; o < m_Open.size();o++)
 			{
 				if (nodeNew[i].codSelf == m_Open[o].codSelf)
 				{
 					bRet = true;
 					break;
 				}
 			}
 			if (bRet)
 			{
 				continue;
 			}
			//�Ƿ���Close����
 			for (int o = 0; o < m_Close.size(); o++)
 			{
 				if (nodeNew[i].codSelf == m_Close[o].codSelf)
 				{
 					bRet = true;
 					break;
 				}
 			}
 			if (bRet)
 			{
 				continue;
 			}
//=====û���Ż�����================================================================================




			//���ϸ�ĵ㱣�浽Open����
			m_Open.push_back(nodeNew[i]);




//=====�Ż�����=====================================================================================



			//m_pVir[y * m_MapWidth + x].isOpen = true;




//=====�Ż�����=====================================================================================
		}

	}//while
}

void CAstar::GetPath()
{
	//���ݸ��ڵ�
	m_Path.clear();//���ԭ����·��
	int nSize = m_Close.size();
	int nIndex = nSize - 1;

	while (true)
	{
		for (int i = 0; i < nSize;i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				return;
			}
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				m_Path.push_back(m_Close[i].codSelf);
				nIndex = i;
				break;
			}
		}
	}
}


void CAstar::PrintWall()
{
	PrintChar(m_Start.X, m_Start.Y, "S", 13);
	PrintChar(m_End.X, m_End.Y, "E", 13);
	m_pMap[m_Start.Y*m_MapWidth + m_Start.X] = 10;

	while (true)
	{
		DWORD dwRead;
		INPUT_RECORD ir;
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ir, 1, &dwRead);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				{
					break;
				}
				COORD cod = ir.Event.MouseEvent.dwMousePosition;
				m_pMap[cod.Y*m_MapWidth + cod.X / 2] = 1;
				PrintChar(cod.X / 2, cod.Y, "��", 14);
			}
		}
	}
}
void CAstar::PrintPath()
{
	for (int i = m_Path.size() - 1; i >= 0; i--)
	{
		PrintChar(m_Path[i].X, m_Path[i].Y, "@", 10);
	}
}
void CAstar::PrintChar(int x, int y, char* pStr, short color)
{
	DWORD dwWrite;
	COORD pos = { x * 2, y };
	int nLen = strlen(pStr);
	WORD* pColor = new WORD[nLen * 2];
	wmemset((wchar_t*)pColor, color, nLen * 2);
	WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pColor, nLen * 2, pos, &dwWrite);
	WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), pStr, nLen, pos, &dwWrite);
	delete[] pColor;
	pColor = nullptr;
}