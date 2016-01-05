//Ying Xu
//xuying@usc.edu
//9751662776
//2014-11-9

#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

#define ImageHeight 181
#define ImageWidth 282
#define ByteperPixel 3

void ImageRead( unsigned char ImageData[ImageHeight][ImageWidth][ByteperPixel], const char * FileName )
{
	FILE * ReadFile; //Read the Image
	if ( !(ReadFile = fopen(FileName,"rb")))
	{
		cout << "Input Image Error!\n"<<endl;
		system("pause");
		exit(1);
	}
	fread(ImageData, sizeof(unsigned char), ImageHeight*ImageWidth*ByteperPixel, ReadFile);
	fclose(ReadFile);
}

void GImageWrite(unsigned char ImageData[ImageHeight][ImageWidth] , const char * FileName)
{
	FILE * WriteFile;
	if (!(WriteFile = fopen(FileName, "wb")))
	{
		cout<<"Input Image Error!\n"<<endl;
		system("pause");
		exit(1);
	}
	fwrite(ImageData, sizeof(unsigned char), ImageHeight*ImageWidth, WriteFile);
	fclose(WriteFile);
}

void ImageWrite(unsigned char ImageData[ImageHeight][ImageWidth][3], const char * FileName)
{
	FILE * WriteFile;
	if (!(WriteFile = fopen(FileName, "wb")))
	{
		cout<<"Input Image Error!\n"<<endl;
		system("pause");
		exit(1);
	}
	fwrite(ImageData, sizeof(unsigned char), ImageHeight*ImageWidth*3, WriteFile);
	fclose(WriteFile);
}

int Left(unsigned char Input[ImageHeight][ImageWidth],int top,int bottom,int left)
{
    int left_bd=0;
    for(int j=left;j<ImageWidth;j++)
    {
        for(int i=top;i<=bottom;i++)
        {
            if(Input[i][j]==255)
            {
                left_bd=j;
                break;
            }
        }
        if(left_bd!=0)
            break;
    }
    return left_bd;
    
}

int Right(unsigned char Input[ImageHeight][ImageWidth],int top,int bottom,int left)
{
    int right_bd=0;
    for(int j=left+1;j<ImageWidth;j++)
    { int s=0;
        for(int i=top;i<=bottom;i++)
        {
            s=s+Input[i][j];
        }
        if(s==0)
        {
            right_bd=j-1;
            break;
        }
    }
    return right_bd;
}

int Top(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top, int bottom)
{
    int top_bd=0;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                top_bd=i;
                break;
            }
        }
        if(top_bd!=0)
            break;
    }
    
    return top_bd;
}

int Bottom(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top)
{
    int bottom_bd=0;
    for(int i=top;i<ImageHeight;i++)
    {
        int s=0;
        for(int j=left;j<=right;j++)
            s=s+Input[i][j];
        if(s==0)
        {
            bottom_bd=i-1;
            break;
        }
    }
    return bottom_bd;
}

void Boundary_Mark(unsigned char Input[ImageHeight][ImageWidth][3],int left, int right, int top,int bottom)
{
    for(int i=top;i<=bottom;i++)
        for(int j=left;j<=right;j++)
        {
            if(i==top||i==bottom||j==left||j==right)
                Input[i][j][0]=255;
        }
}

double Hori_Ave(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    int count=0;
    int hori=0;
    double hori_ave=0;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                count++;
                hori+=j;
            }
        }
    }
    hori_ave=((hori/count)-left)/double(right-left);
    return hori_ave;
}

double Verti_Ave(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    int count=0;
    int verti=0;
    double verti_ave=0;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                count++;
                verti+=i;
            }
        }
    }
    verti_ave=(top-(verti/count))/double(top-bottom);
    return verti_ave;
}

double Hori_sym(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    double count=0;
    double sym=0;
    double hori_sym;
    int center_x,center_y;
    center_y=(left+right)/2;
    center_x=(top+bottom)/2;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                count++;
                if(Input[i][2*center_y-j]==255)
                    sym++;
            }
        }
    }
    
    hori_sym=sym/count;
    return hori_sym;
}

double Verti_sym(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    double count=0;
    double sym=0;
    double verti_sym;
    int center_x,center_y;
    center_y=(left+right)/2;
    center_x=(top+bottom)/2;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                count++;
                if(Input[2*center_x-i][j]==255)
                    sym++;
            }
        }
    }
    
    verti_sym=sym/count;
    return verti_sym;
}

double Dia_sym(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    double count=0;
    double sym=0;
    double dia_sym;
    int center_x,center_y;
    center_y=(left+right)/2;
    center_x=(top+bottom)/2;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                count++;
                if(Input[2*center_x-i][2*center_y-j]==255)
                    sym++;
            }
        }
    }
    
    dia_sym=sym/count;
    return dia_sym;
}

double Circular(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    double count1=0;
    double count2=0;
    double cir=0;
    
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            if(Input[i][j]==255)
            {
                count1++;
                if(Input[i-1][j]==0)
                    count2++;
                if(Input[i+1][j]==0)
                    count2++;
                if(Input[i][j+1]==0)
                    count2++;
                if(Input[i][j-1]==0)
                    count2++;
            }
        }
    }
    cir=4*3.1416*count1/pow(count2,2);
    return cir;
}

double Euler(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    double count1=0;
    double count2=0;
    double count3=0;
    double euler=0;
    int s=0;
    
    for(int i=top;i<=bottom+1;i++)
    {
        for(int j=left;j<=right+1;j++)
        {
            
            s=Input[i-1][j-1]+Input[i-1][j]+Input[i][j-1]+Input[i][j];
            if(s==255)
                count1++;
            if(s==(255*3))
                count3++;
            if((Input[i-1][j-1]*Input[i][j])!=0&&(Input[i-1][j]+Input[i][j-1])==0)
                count2++;
            if((Input[i-1][j]*Input[i][j-1])!=0&&(Input[i-1][j-1]+Input[i][j])==0)
                count2++;
        }
    }
    euler=(count1-count3-count2*2)/4;
    return euler;
}

double Aspect(int left, int right, int top,int bottom)
{
    
    double aspect;
    aspect=double(bottom-top)/(right-left);
    return aspect;
}

double Occpancy(unsigned char Input[ImageHeight][ImageWidth],int left, int right, int top,int bottom)
{
    
    double occu;
    double count1;
    double count2;
    for(int i=top;i<=bottom;i++)
    {
        for(int j=left;j<=right;j++)
        {
            count1++;
            if(Input[i][j]==255)
                count2++;
        }
    }
    
    
    occu=count2/count1;
    return occu;
    
}









int main()
{
    unsigned char OriImage[ImageHeight][ImageWidth][ByteperPixel]={0};
    unsigned char Input[ImageHeight][ImageWidth][ByteperPixel]={0};
    unsigned char BinaryImage[ImageHeight][ImageWidth]={0};
    unsigned char cut[ImageHeight][ImageWidth][3]={0};
    
    ImageRead(OriImage, "/Users/Aria/Documents/USC/569/hw3/hw3_images/OCR_test1.raw");
    
    
    for(int i=0;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            if(OriImage[i][j][0]>100&&OriImage[i][j][1]<60&&OriImage[i][j][2]<60)
            {
                Input[i][j][0]=255;
                Input[i][j][1]=255;
                Input[i][j][2]=255;
            }
            else
            {
                Input[i][j][0]=OriImage[i][j][0];
                Input[i][j][1]=OriImage[i][j][1];
                Input[i][j][2]=OriImage[i][j][2];
            }
            
        }
    }
    
    
    ImageWrite(Input, "/Users/Aria/Documents/USC/569/hw3/hw3_images/inpt.raw");
    
    for(int i=0;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            for(int k=0;k<3;k++)
            if(Input[i][j][k]<150)
                BinaryImage[i][j]=255;
            else
                BinaryImage[i][j]=0;
        }
    }
    
    int t=0,flag=0;
    for(int j=0;j<ImageWidth;j++)
    {
        for(int i=0;j<ImageHeight;i++)
        {
            if(BinaryImage[i][j]==255)
            {
              t=i;
                flag=1;
                break;
            }
        }
       if(flag==1)
           break;
    }
    
    
  
    
    for(int i=t-10;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            BinaryImage[i][j]=0;
        }
    }
    
    
    int t1=0,t2=0,t3=0;
    flag=0;
    for(int j=0;j<ImageWidth;j++)
    {
        for(int i=0;j<ImageHeight;i++)
        {
            if(BinaryImage[i][j]==255)
            {
                t1=j;
                flag=1;
                break;
            }
        }
        if(flag==1)
            break;
    }
    
    for(int j=0;j<=t1+80;j++)
    {
        for(int i=0;i<ImageHeight;i++)
        {
            BinaryImage[i][j]=0;
        }
    }
    
    
    flag=0;
    for(int j=ImageWidth-1;j>0;j--)
    {
        for(int i=0;i<ImageHeight;i++)
        {
            if(BinaryImage[i][j]==255)
            {
                t2=j;
                flag=1;
                break;
            }
        }
        if(flag==1)
            break;
    }
    
    for(int j=ImageWidth-1;j>=t2-40;j--)
    {
        for(int i=0;i<ImageHeight;i++)
        {
            BinaryImage[i][j]=0;
        }
    }
    
    
    for(int i=0;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            if(BinaryImage[i][j]==255)
            {
                t3=i;
                flag=1;
                break;
            }
        }
        if(flag==1)
            break;
    }

    for(int i=0;i<t3+52;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            BinaryImage[i][j]=0;
        }
    }

GImageWrite(BinaryImage, "/Users/Aria/Documents/USC/569/hw3/hw3_images/binary2.raw");
    
    
    int top[2]={0};
    int bottom[2]={0};
    for(int i=0;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            if(BinaryImage[i][j]==255)
            {
                top[0]=i;
                break;
            }
        }
        if(top[0]!=0)
            break;
    }
    
    
    
    for(int i=top[0];i<ImageHeight;i++)
    {
        int s=0;
        for(int j=0;j<ImageWidth;j++)
        {
            s=s+BinaryImage[i][j];
        }
        if(s==0)
        {
            bottom[0]=i-1;
            break;
        }
        if(bottom[0]!=0)
            break;
    }
    
    for(int i=bottom[0]+1;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            if(BinaryImage[i][j]==255)
            {
                top[1]=i;
                break;
            }
        }
        if(top[1]!=0)
            break;
    }
    
    for(int i=top[1]+1;i<ImageWidth;i++)
    {
        int s=0;
        for(int j=0;j<ImageWidth;j++)
        {
            s=s+BinaryImage[i][j];
        }
        if(s==0)
        {
            bottom[1]=i-1;
            break;
        }
        if(bottom[1]!=0)
            break;
    }
    
    
    
    
    int left1[7]={0};
    int right1[7]={0};
    
    left1[0]=Left(BinaryImage,top[0],bottom[0],0);
    right1[0]=Right(BinaryImage,top[0],bottom[0],left1[0]);
    
    for(int i=1;i<4;i++)
    {
        left1[i]=Left(BinaryImage,top[0],bottom[0],right1[i-1]+1);
        right1[i]=Right(BinaryImage,top[0],bottom[0],left1[i]);
    }
    
    left1[4]=Left(BinaryImage,top[0],bottom[0],right1[3]+1);
   
   
    for(int j=left1[4]+1;j<ImageWidth;j++)
    { int s=0;
        for(int i=top[0];i<=bottom[0];i++)
        {
            s=s+BinaryImage[i][j];
        }
        if(s==255)
        {   right1[4]=j-1;
            break;
        }
    }
    
    for(int i=top[0];i<=bottom[0];i++)
        BinaryImage[i][right1[4]+1]=0;

    

    for(int i=5;i<7;i++)
    {
        left1[i]=Left(BinaryImage,top[0],bottom[0],right1[i-1]+1);
        right1[i]=Right(BinaryImage,top[0],bottom[0],left1[i]);
    }
    
    for(int i=0;i<ImageHeight;i++)
    {
        for(int j=0;j<ImageWidth;j++)
        {
            for(int k=0;k<3;k++)
                cut[i][j][k]=BinaryImage[i][j];
            
        }
    }
    
    int top1[7]={0};
    int bottom1[7]={0};
    
    for(int i=0;i<6;i++)
    {
        top1[i]=Top(BinaryImage,left1[i],right1[i],top[0],bottom[0]);
        bottom1[i]=Bottom(BinaryImage,left1[i],right1[i],top1[i]);
    }
    top1[6]=Top(BinaryImage,left1[6],right1[6],top[0],bottom[0]);
    
    for(int j=left1[6];j<=right1[6];j++)
    {
        for(int i=bottom[0];i>=top[0];i--)
            if(BinaryImage[i][j]==255)
            {
                bottom1[6]=i+1;
                break;
            }
        if(bottom1[6]!=0)
            break;
    }
    

    
    int left2[8]={0};
    int right2[8]={0};
    left2[0]=Left(BinaryImage,top[1],bottom[1],0);
    right2[0]=Right(BinaryImage,top[1],bottom[1],left2[0]);
    
    for(int i=1;i<8;i++)
    {
        left2[i]=Left(BinaryImage,top[1],bottom[1],right2[i-1]+1);
        right2[i]=Right(BinaryImage,top[1],bottom[1],left2[i]);
    }
    
    
    int top2[8]={0};
    int bottom2[8]={0};
    
    for(int i=0;i<8;i++)
    {
        top2[i]=Top(BinaryImage,left2[i],right2[i],top[1],bottom[1]);
        bottom2[i]=Bottom(BinaryImage,left2[i],right2[i],top2[i]);
    }
    
    
    
    
    
  
    
    
    for(int i=0;i<7;i++)
        Boundary_Mark(cut, left1[i]-1, right1[i]+1, top1[i]-1, bottom1[i]+1);
    
    for(int i=0;i<8;i++)
        Boundary_Mark(cut, left2[i]-1, right2[i]+1, top2[i]-1, bottom2[i]+1);
    
    
    
    ImageWrite(cut, "/Users/Aria/Documents/USC/569/hw3/hw3_images/ROI2.raw");
    
    double hori_ave[15]={0};
    double verti_ave[15]={0};
    double hori_sym[15]={0};
    double verti_sym[15]={0};
    double dia_sym[15]={0};
    double circular[15]={0};
    double euler[15]={0};
    double aspect[15]={0};
    double occu[15]={0};
    
    for(int i=0;i<7;i++)
    {
        hori_ave[i]=Hori_Ave(BinaryImage,left1[i], right1[i], top1[i], bottom1[i]);
        verti_ave[i]=Verti_Ave(BinaryImage,left1[i], right1[i],  top1[i], bottom1[i]);
        hori_sym[i]=Hori_sym(BinaryImage,left1[i], right1[i],  top1[i], bottom1[i]);
        verti_sym[i]=Verti_sym(BinaryImage,left1[i], right1[i],  top1[i], bottom1[i]);
        dia_sym[i]=Dia_sym(BinaryImage,left1[i], right1[i],  top1[i], bottom1[i]);
        circular[i]=Circular(BinaryImage,left1[i], right1[i], top1[i], bottom1[i]);
        euler[i]=Euler(BinaryImage,left1[i], right1[i],  top1[i], bottom1[i]);
        aspect[i]=Aspect(left1[i], right1[i], top1[i], bottom1[i]);
        occu[i]=Occpancy(BinaryImage,left1[i], right1[i],  top1[i], bottom1[i]);
        
        
    }
    for(int i=0;i<8;i++)
    {
        hori_ave[i+7]=Hori_Ave(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        verti_ave[i+7]=Verti_Ave(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        hori_sym[i+7]=Hori_sym(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        verti_sym[i+7]=Verti_sym(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        dia_sym[i+7]=Dia_sym(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        circular[i+7]=Circular(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        euler[i+7]=Euler(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        aspect[i+7]=Aspect(left2[i], right2[i], top2[i], bottom2[i]);
        occu[i+7]=Occpancy(BinaryImage,left2[i], right2[i], top2[i], bottom2[i]);
        
        
    }
   
    
    
    
    //-----------------decision tree-----------
    
    char symbol[15]={0};
    
    
    for(int k=0;k<15;k++)
    {
        if(euler[k]==-1)//---B 8
        {
            if(dia_sym[k]<=0.8)
                symbol[k]='B';
            else
                symbol[k]='8';
        }
        if(euler[k]==2)
            symbol[k]=':';
        if(euler[k]==0)//----PDe4690
        {
            if(verti_sym[k]>=0.8)//----D0
            {
                if(hori_sym[k]>=0.7)
                    symbol[k]='0';
                else
                    symbol[k]='D';
            }
            else//----Pe469
            {
                if(verti_ave[k]>=0.5)
                    symbol[k]='6';
                else//-----Pe49
                {
                    if(hori_ave[k]>=0.5)
                    {
                        if(circular[k]>0.15)
                            symbol[k]='4';
                        else
                            symbol[k]='9';
                    }
                    else
                    {
                        if(aspect[k]>=1.3)
                            symbol[k]='P';
                        else
                            symbol[k]='e';
                    }
                    
                }
            }
        }
        if(euler[k]==1)//-----SELYCly12357/
        {
            if(hori_sym[k]>=0.67)//------Yly
            {
                if(verti_sym[k]>=0.9)
                    symbol[k]='l';
                else
                {
                    if(aspect[k]>=1.4)
                        symbol[k]='y';
                    else
                        symbol[k]='Y';
                }
            }
            else//----SELC12357/
            {
                if(dia_sym[k]>=0.7)
                {
                    if(circular[k]>=0.15)
                        symbol[k]='/';
                    else
                        symbol[k]='S';
                }
                else//------ELC12357
                {
                    if(verti_sym[k]>=0.5)//------ELC13
                    {
                        if(hori_ave[k]<0.5)//-----ELC
                        {
                            if(circular[k]>0.2)
                                symbol[k]='L';
                            else
                            {
                                if(hori_sym[k]>0.4)
                                    symbol[k]='E';
                                else
                                    symbol[k]='C';
                            }
                        }
                        else
                        {
                            if(circular[k]>0.2)
                                symbol[k]='1';
                            else
                                symbol[k]='3';
                        }
                    }
                    else
                    {
                        if(circular[k]>0.15)
                            symbol[k]='7';
                        else
                        {
                            if(dia_sym[k]>0.5)
                                symbol[k]='5';
                            else
                                symbol[k]='2';
                        }
                    }
                }
            }
        }
    }
    
    for(int i=0;i<15;i++)
    {
        cout<<symbol[i];
    }
 
    cout<<"\n";
}





