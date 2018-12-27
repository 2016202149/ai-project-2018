#include <TraceApp.h>//����ʶ���
int Left_motor=8;     //����(IN3) ���0  ǰ��   ���1 ����
int Left_motor_pwm=9;     //����PWM����
int Right_motor_pwm=10;    // �ҵ��PWM����
int Right_motor=11;    // �ҵ������(IN1)  ���0  ǰ��   ���1 ����

TraceApp obj(Serial, 9600); //�����͵��Դ��ڲ����ʣ�����ʶ��ר�ã�
void setup() {
  obj.begin(); //��ʼ��,ע��:���治��Ҫ����Serial.begin()!

  pinMode(Left_motor,OUTPUT); // PIN 8 8����PWM����
  pinMode(Left_motor_pwm,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_pwm,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor,OUTPUT);// PIN 11 (PWM)
}




/********ǰ���Ӻ���**************/
void  run(int PWM_L,int PWM_R)                         
{ 
   digitalWrite(Right_motor,LOW);  // �ҵ��ǰ��
  digitalWrite(Right_motor_pwm,HIGH);  // �ҵ��ǰ��     
  analogWrite(Right_motor_pwm,PWM_R);//PWM����0~255���٣������ֲ���������
  
  
  digitalWrite(Left_motor,LOW);  // ����ǰ��
  digitalWrite(Left_motor_pwm,HIGH);  //����PWM     
  analogWrite(Left_motor_pwm,PWM_L);//PWM����0~255���٣������ֲ���������
}

/********���˺���**************/
void  back(int PWM_L,int PWM_R)                    
{ 
   digitalWrite(Right_motor,HIGH);  // �ҵ������
  digitalWrite(Right_motor_pwm,HIGH);  // �ҵ��ǰ��     
  analogWrite(Right_motor_pwm,PWM_R);//PWM����0~255���٣������ֲ���������
  
  
  digitalWrite(Left_motor,HIGH);  // ��������
  digitalWrite(Left_motor_pwm,HIGH);  //����PWM     
  analogWrite(Left_motor_pwm,PWM_L);//PWM����0~255���٣������ֲ���������
}

/*********ֹͣ����**************/
void brake()                              
{  
   digitalWrite(Right_motor_pwm,HIGH);  // �ҵ��PWM �������0      
  analogWrite(Right_motor_pwm,0);//PWM����0~255���٣������ֲ���������

  digitalWrite(Left_motor_pwm,HIGH);  //����PWM �������0          
  analogWrite(Left_motor_pwm,0);//PWM����0~255���٣������ֲ���������
}






int x,y;
void follow(){
  obj.routine();//����ʶ�𣻾���������һ��Ƶ������
  if (obj.valid())
  {
  	x=obj.getX();//x����
     y=obj.getY();//y����
    //int t=obj.getT(); //�����С

    int yc=y-174;//yƫ�Ʋ�ֵ
    int xc=x-124;//xƫ�Ʋ�ֵ
    
    xc=abs(xc);//x��ֵ����ֵ
    yc=abs(yc);//t��ֵ����ֵ
    int big_pwm=0;
	int small_pwm=0;
    big_pwm=yc*2+xc*1.7;//�ϴ��pwm   
    small_pwm=yc*2-xc*1.7;//��С��pwm 
    big_pwm=constrain(big_pwm,0,180);//����PWM
    small_pwm=constrain(small_pwm,0,180);//����PWM
    
    if((x>70)&&(x<225)&&(y<75)){  //��ǰ�� 
    	run(150,150);
	}
	if((x>70)&&(x<225)&&(y>261)){  //���� 
    	back(150,150);
	}
    if(x<130 && y<156){            //���Ͻ� 
    	run(big_pwm,small_pwm);
	}
	if(x>130 && y<156){           //���Ͻ� 
		run(small_pwm,big_pwm);
	}
	if(x<130 && y>156){           //���½� 
		back(small_pwm,big_pwm);
	}
	if(x>130 && y>156){           //���½� 
		back(big_pwm,small_pwm);
	}
  }
}






void loop() {
  obj.routine();//����ʶ�𣻾���������һ��Ƶ������
  follow();
}


