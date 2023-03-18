#include "Tetris.h"
Tetris::Tetris()
{
	dx = 0; //X ����ƫ����
	rotate = false; //�Ƿ���ת
	colorNum = 1; //ɫ�����ɫ
	timer = 0;
	delay = DALAYVALUE; //������ٶ�
}



Tetris::~Tetris()
{
}
int Tetris::holdcolorNum = 0, Tetris::holdShapeNum = 0;
Vector2i Tetris::holdSquare[4] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };

void Tetris::Initial(Texture* tex)
{
	tTiles = tex;
	dx = 0; //X ����ƫ����
	rotate = false; //�Ƿ���ת
	hold = false;
	hardDrop = false; //�Ƿ�Ӳ��

	colorNum = 1; //ɫ�����ɫ
	timer = 0;
	delay = DALAYVALUE; //������ٶȣ�

	b7Int = 0;

	animationFlag = true; //��������,����Ϸ�Ƿ�ʼ����
	animationCtrlValue = 1.0;

	if (role == rolePLAYER1)
	{
		mCornPoint = { P1_STAGE_CORNER_X, P1_STAGE_CORNER_Y };
		nextSquareCornPoint = { P1_NEXT_CORNER_X, P1_NEXT_CORNER_Y };
	}
	if (role == rolePLAYER2)
	{
		mCornPoint = { P2_STAGE_CORNER_X, P2_STAGE_CORNER_Y };
		nextSquareCornPoint = { P2_NEXT_CORNER_X, P2_NEXT_CORNER_Y };
	}
	holdSquareCornPoint = { HOLD_CORNER_X, HOLD_CORNER_Y };
	holdShapeNum = -1;//��Ϸ��ʼʱ��hold ����ͼ������һ���쳣ֵ
	sTiles.setTexture(*tTiles);
	//��ʼ������ͼ��
	colorNum = 1 + rand() % 7;
	currentShapeNum = Bag7();//rand() % 7;
	//�����¸�����ͼ��
	nextcolorNum = 1 + rand() % 7;
	nextShapeNum = Bag7();//rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		currentSquare[i].x = Figures[currentShapeNum][i] % 2 + STAGE_WIDTH / 2;
		currentSquare[i].y = Figures[currentShapeNum][i] / 2;
		nextSquare[i].x = Figures[nextShapeNum][i] % 2;
		nextSquare[i].y = Figures[nextShapeNum][i] / 2;

		animationRow[i] = -1;//Ҫ���Ŷ���������, -1 Ϊ�쳣ֵ�����������˼
	}

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			Field[i][j] = 0;
		}
	}
}

void Tetris::Input(sf::Event event)
{
	if (role == rolePLAYER1)//��� 1 �İ�����Ӧ
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::W)
				if (currentShapeNum != shapeO)
				    rotate = true;
			if (event.key.code == Keyboard::A)
				dx = -1;
			else if (event.key.code == Keyboard::D)
				dx = 1;
			if (event.key.code == Keyboard::S)
				delay = DALAYVALUE / 10;
		}
		
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::LControl)
				hold = true;
			if (event.key.code == Keyboard::Space)
				hardDrop = true;
			if (event.key.code == Keyboard::A || event.key.code == Keyboard::D)
				dx = 0;
			if (event.key.code == Keyboard::S)
				delay = DALAYVALUE;
	    }
	}
	if (role == rolePLAYER2)//��� 2 �İ�����Ӧ
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up)
				if (currentShapeNum != shapeO)
					rotate = true;
			if (event.key.code == Keyboard::Left)
				dx = -1;
			else if (event.key.code == Keyboard::Right)
				dx = 1;
			if (event.key.code == Keyboard::Down)
				delay = 0.05;
		}
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::RControl)
				hold = true;
			if (event.key.code == Keyboard::Enter)
				hardDrop = true;
			if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right)
				dx = 0;
			if (event.key.code == Keyboard::Down)
				delay = DALAYVALUE;
		}
	}
}
void Tetris::Logic()
{
	if (!animationFlag)
		traditionLogic();
	//����з����·����������������ж��Ƿ��ж������ţ��� new �µķ���
	if (newShapeFlag)
	{
		if (animationFlag == false)
		{
			///////check lines//////////
			checkLine();
			if (animationFlag == false)
				newShapeFunc();//���Ӧ�þ�Ҫ�����µķ���;ͼ�����ɺ��������ٸ���Flag��״̬
			isWin();
		}
		else
	    {
			animationCtrlValue -= 0.1;
			if (animationCtrlValue < 0)
			{
				animationFlag = false;
				animationCtrlValue = 1.0;
				for (int i = 0; i < 4; i++)
					animationRow[i] = -1;//����Ӧ�ö���������֮������㣬��������ɿ�ܽṹ���ң����� - 1 Ϊ�쳣ֵ�����������˼
					
				clearLine();
				newShapeFunc();
			}
		
	    }
	}
	
}
bool Tetris::hitTest()
{
	 for (int i = 0; i < 4; i++)
		 if (currentSquare[i].x < 0 || currentSquare[i].x >= STAGE_WIDTH || currentSquare[i].y >= STAGE_HEIGHT)
		 return false;
	 else if (Field[currentSquare[i].y][currentSquare[i].x])
		 return false;
	
	 return true;
}
void Tetris::yMove()
{
	for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i].y += 1;
	}

	if (!hitTest())//���ײ����
	{
		for (int i = 0; i < 4; i++)
			Field[tempSquare[i].y][tempSquare[i].x] = colorNum;
            //���ڶ����������Ҫ���˴������˴����װ�����Ƶ��ⲿ���ȶ����������� new �µ�ͼ�Ρ�
			newShapeFlag = true; //ײ���˾�Ҫ���µ�ͼ������
	}

}
void Tetris::Draw(sf::RenderWindow* window)
{
	if (animationFlag == false)//�����ܿ�
	{
		//���� Shadow �ķ���
		for (int i = 0; i < 4; i++)
		{
			sTiles.setTextureRect(IntRect(colorNum * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(shadowSquare[i].x * GRIDSIZE, shadowSquare[i].y * GRIDSIZE);
			sTiles.setColor(Color(50, 50, 50, 255)); //������Ӱ����ɫ
			sTiles.move(mCornPoint.x, mCornPoint.y); //offset
			window->draw(sTiles);
			sTiles.setColor(Color(255, 255, 255, 255));//��ɫ�Ļ�ԭɫ
		}
        //���ƻ�ķ���
		for (int i = 0; i < 4; i++)
		{
			sTiles.setTextureRect(IntRect(colorNum * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(currentSquare[i].x * GRIDSIZE, currentSquare[i].y * GRIDSIZE);
			sTiles.move(mCornPoint.x, mCornPoint.y); //offset
			window->draw(sTiles);
		}
	}
	//���ƹ̶��ķ���
	for (int i = 0; i < STAGE_HEIGHT; i++)
		if (i == animationRow[0] || i == animationRow[1] || i == animationRow[2] || i == animationRow[3])
		    animationFunc(i);//���������е�ʱ��ִ����Ч����
	    else
	        for (int j = 0; j < STAGE_WIDTH; j++)
	        {
		        if (Field[i][j] == 0)
			        continue;
		        sTiles.setTextureRect(IntRect(Field[i][j] * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		        sTiles.setPosition(j * GRIDSIZE, i * GRIDSIZE);
		        sTiles.move(mCornPoint.x, mCornPoint.y); //offset
		        //animationFlag = false;
		        window->draw(sTiles);
	        }
	//���� Next ���ķ���
	for (int i = 0; i < 4; i++)
	{
		sTiles.setTextureRect(IntRect(nextcolorNum * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(nextSquare[i].x * GRIDSIZE, nextSquare[i].y * GRIDSIZE);
		sTiles.move(nextSquareCornPoint.x, nextSquareCornPoint.y); //offset
		window->draw(sTiles);
	}
	//���� Hold ���ķ���
	if (holdShapeNum > -1)//hold ��ͼ������ʱ����л���
		for (int i = 0; i < 4; i++)
		{
			sTiles.setTextureRect(IntRect(holdcolorNum * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(holdSquare[i].x * GRIDSIZE, holdSquare[i].y * GRIDSIZE);
			sTiles.move(holdSquareCornPoint.x, holdSquareCornPoint.y); //offset
			window->draw(sTiles);
		}
}
int Tetris::Bag7()
{
	int num;
	srand(time(NULL));
	num = rand() % 7;
	for (int i = 0; i < b7Int; i++)
	{
		if (b7array[i] == num)
		{
			i = -1;//i++����㣬�������±���
			num = rand() % 7;
		}
	}
	b7array[b7Int] = num;
	
	b7Int++;
	if (b7Int == 7)
	{
		b7Int = 0;
		for (int i = 0; i < 7; i++)
			b7array[i] = 0;
	}
	return num;
}
void Tetris::holdFunc()
{
	Vector2i backUpSquare[4];
	tempcolorNum = holdcolorNum;
	tempShapeNum = holdShapeNum;

	holdcolorNum = colorNum;
	holdShapeNum = currentShapeNum;

	for (int i = 0; i < 4; i++)
	{
		holdSquare[i].x = Figures[holdShapeNum][i] % 2;
		holdSquare[i].y = Figures[holdShapeNum][i] / 2;
		tempSquare[i].x = Figures[tempShapeNum][i] % 2;
		tempSquare[i].y = Figures[tempShapeNum][i] / 2;
		backUpSquare[i] = currentSquare[i];
	}
	if (tempShapeNum < 0)//hold ��ͼ�ε��쳣ֵ��ʾ hold ��Ϊ�յ�״̬������Ҫ��Next��ȡֵ
	{//���ԭ hold ��Ϊ�գ���ǰͼ�δ� Next ȡ
		newShapeFunc();//�˴���������˷�װ 20191122 ����
	}
	else//��ǰͼ��ȡԭ�� hold ͼ�ε�ֵ���ȷ�������
	{
		colorNum = tempcolorNum;
		currentShapeNum = tempShapeNum;
		//�� hold ���û������ķ���ͼ�Σ�����̨������ļ��㡣
		int minCurrentX = currentSquare[0].x,
			minCurrentY = currentSquare[0].y,
			minTempX = tempSquare[0].x,
			minTempY = tempSquare[0].y;
		int dx, dy;
		for (int i = 1; i < 4; i++)
		{
			if (currentSquare[i].x < minCurrentX)
				minCurrentX = currentSquare[i].x;
			if (currentSquare[i].y < minCurrentY)
				minCurrentY = currentSquare[i].y;
			if (tempSquare[i].x < minTempX)
				minTempX = tempSquare[i].x;
			if (tempSquare[i].y < minTempY)
				minTempY = tempSquare[i].y;
		}
		dx = minCurrentX - minTempX;
		dy = minCurrentY - minTempY;

		for (int i = 0; i < 4; i++)
		{
			currentSquare[i].x = tempSquare[i].x + dx;
			currentSquare[i].y = tempSquare[i].y + dy;
			holdSquare[i].x = Figures[holdShapeNum][i] % 2;
			holdSquare[i].y = Figures[holdShapeNum][i] / 2;
		}
	}
	if (!hitTest()) //���ײ����
	{
		colorNum = holdcolorNum;
		holdcolorNum = tempcolorNum;
		holdShapeNum = tempShapeNum;
		for (int i = 0; i < 4; i++)
		{
			currentSquare[i] = backUpSquare[i];
			holdSquare[i].x = Figures[holdShapeNum][i] % 2;
			holdSquare[i].y = Figures[holdShapeNum][i] / 2;
		}
	}
}

void Tetris::xMove()
{
    for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i].x += dx;
	}
	if (!hitTest()) //���ײ����
		for (int i = 0; i < 4; i++)
			currentSquare[i] = tempSquare[i];//�����ҵı߽磬�����Ƴ��߽�
}
void Tetris::rotateFunc()
{
	for (int j = 0; j < 4; j++)//wall kick ����ƫ��
	{
		Vector2i p = currentSquare[j]; //������ת���ĵ�
		for (int i = 0; i < 4; i++)
		{//˳ʱ����ת 90 ��
			int x = currentSquare[i].y - p.y;//ԭ Y ����������ĵ�Ĳ�ֵ����Ϊ�µĲ�ֵ�����ݸ� X ����
			int y = currentSquare[i].x - p.x;//ԭ X ����������ĵ�Ĳ�ֵ����Ϊ�µĲ�ֵ�����ݸ� Y ����
			currentSquare[i].x = p.x - x;//������ X=���ĵ�����-�µ� X �����ֵ
			currentSquare[i].y = p.y + y;//������ Y=���ĵ�����+�µ� Y �����ֵ
		}
		if (!hitTest()) //���ײ����
			for (int i = 0; i < 4; i++)
			currentSquare[i] = tempSquare[i];
		else
		{
			if (currentShapeNum == shapeS)
				if (j != 0) //������ķ���ƫ�ƣ����л����ġ�ͷ�ļ���Ԥ��ֵ�����ĵ�Ǳ�ڿ�����������
				{
				    p = currentSquare[0];
				    currentSquare[0] = currentSquare[1];
				    currentSquare[1] = p;
				}
			break; // ����ѭ��
		}
	}
}
void Tetris::checkLine()
{
	int k = STAGE_HEIGHT - 1;
	int yCount = 0;
	for (int i = STAGE_HEIGHT - 1; i > 0; i--)
	{
		int xCount = 0;
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (Field[i][j])
				xCount++;
			//Field[k][j] = Field[i][j];//�½�
		}
		if (xCount < STAGE_WIDTH)
			k--;
		
		else
		{
			animationRow[yCount] = i;//Ҫ���Ŷ���������
			yCount++;
			animationFlag = true;
		}
	}
	switch (yCount)
	{
	case 1:
		score += 10;
		break;
	case 2:
		score += 30;
		break;
	case 3:
		score += 60;
		break;
	case 4:
		score += 100;
		break;
	}
	//�÷ֺ�Ķ�������
}
void Tetris::hardDropFunc()
{
	for (int i = 0; i < 4; i++) //�����ˣ�������һ��λ��
	{
		currentSquare[i] = shadowSquare[i];
    }
}
void Tetris::slowLoading()//�ײ�����
{
	for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i].y += 1;
	}
	
	if (!hitTest())//���ײ����
	{
		delay = DALAYVALUE * 2;//����ʱ��ʱ���ӳ����γɻ���
	}
	else
	{
		delay = DALAYVALUE;//�Ǵ���ʱ������������ʱ��
	}
	for (int i = 0; i < 4; i++)
		currentSquare[i] = tempSquare[i];
}
void Tetris::shadow()
{
	for (int i = 0; i < 4; i++)
		shadowSquare[i] = currentSquare[i];
	for (int j = 0; j < STAGE_HEIGHT; j++) //һֱ����
	{
		for (int i = 0; i < 4; i++)
			currentSquare[i].y += 1;
		if (!hitTest()) //���ײ����
		{
			for (int i = 0; i < 4; i++) //�����ˣ�������һ��λ��
				currentSquare[i].y -= 1;
			break;
		}
    }
	for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i] = shadowSquare[i];
		shadowSquare[i] = tempSquare[i];
	}
}
void Tetris::traditionLogic()
{
	//hold ����ͼ��
	if (hold)
	{
		holdFunc();
		hold = false;
	}
	//// <- ˮƽ Move -> ///
	xMove();
	
	//////Rotate//////
	if (rotate)
	{
		rotateFunc();
		rotate = false;
	}
	
	slowLoading();
	///////Tick ����//////
	if (timer > delay)
	{
		yMove();
		timer = 0;
	}
	
	shadow();
	
	if (hardDrop)
	{
		hardDropFunc();
		hardDrop = false;
	}
}
void Tetris::clearLine()
{
	int k = STAGE_HEIGHT - 1;
	for (int i = STAGE_HEIGHT - 1; i > 0; i--)
	{
		int xCount = 0;
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (Field[i][j])
				xCount++;
			Field[k][j] = Field[i][j];//�½�
		}
		if (xCount < STAGE_WIDTH)
			k--;
	}
}
void Tetris::newShapeFunc()
{
	//ȡ�¸�����ͼ��
	colorNum = nextcolorNum;
	currentShapeNum = nextShapeNum;
	
	//�����¸�����ͼ��
	nextcolorNum = 1 + rand() % 7;
	nextShapeNum = Bag7();
	
	for (int i = 0; i < 4; i++)
	{
		currentSquare[i] = nextSquare[i];//��ǰ�����
		currentSquare[i].x = currentSquare[i].x + STAGE_WIDTH / 2;
		nextSquare[i].x = Figures[nextShapeNum][i] % 2;
		nextSquare[i].y = Figures[nextShapeNum][i] / 2;
	}
	
	shadow();
	
	newShapeFlag = false;//�����´β����ٽ���
}
void Tetris::animationFunc(int i)
{
	Vector2f p;
	sTiles.scale(animationCtrlValue, animationCtrlValue);
	p = sTiles.getOrigin();
	sTiles.setOrigin(GRIDSIZE / 2, GRIDSIZE / 2);
	sTiles.rotate(360 * animationCtrlValue);
	for (int j = 0; j < STAGE_WIDTH; j++)
	{
		sTiles.setTextureRect(IntRect(Field[i][j] * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(j * GRIDSIZE, i * GRIDSIZE);
		sTiles.move(mCornPoint.x + GRIDSIZE / 2, mCornPoint.y + GRIDSIZE / 2); //offset
		//�÷�����ת����С
		window->draw(sTiles);
	}
	sTiles.scale(1.0 / animationCtrlValue, 1.0 / animationCtrlValue);
	sTiles.rotate(-360 * animationCtrlValue);
	sTiles.setOrigin(p);
}
void Tetris::isWin()
{
	//ԭ��Ӧ������ײ������������жϣ����˴���������λ����һ��Ϊ�㣬��Ϸ������
	//if(!hitTest())
	if (Field[2][5] || Field[2][6])
		gameOver = true;
}