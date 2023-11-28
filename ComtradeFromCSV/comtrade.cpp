#include "Comtrade.hpp"
/*
Comtrade::Comtrade()
{
	Fnetwork = num2str(Fnetwork);
	FileName = FileName;
	Fsampl = num2str(1000000/(SIGNALS(1).TIME(2,1)-SIGNALS(1).TIME(1,1)));
	Nsampl = num2str(length(SIGNALS(1).TIME));
	Time   = SIGNALS(1).TIME;
	CfgFilePrint(FileName,obj.Fnetwork,Fsampl,Nsampl,SIGNALS)
	DatFilePrint(SIGNALS,Time,FileName)
}

void Comtrade::COMTRADEFORM(std::string FileName , std::string VoltageUnits , std::string CurrentUnits , float SIGA , float SIGB , float* DAT)
{

}
//Функция формирования .cfg-файла
void Comtrade::CfgFilePrint(std::string FileName,float Fnetwork,float Fsampl,int Nsampl,float* SIGNALS)
{
	//Создаем пустой текстовый файл с расширением .cfg
	int NASIG=0;//число аналоговых сигналов
	int NDSIG=0;//число дискретных сигналов
	int n    =0;//счетчик номеров сигналов
	NUM  =zeros

	for (int i = 0; i < SIGNALS.size(); i++)
	{
		//Расчет количества аналогов и дискретов:
		if (SIGNALS(1,i).SIGTYPE=='A')
		{//если сигнал аналоговый, то:
			NASIG=NASIG+1;
			int n=n+1;
			NUM(i,1)=n;
		}

		if (SIGNALS(1,i).SIGTYPE=='D')
		{//если сигнал дискретный, то:
			NDSIG=NDSIG+1;
			int n=n+1;
			NUM(i,1)=n;
		}
	}
	//Определяем общее число сигналов, число дискретных и число
	//аналоговых сигналов:
	std::string Ntotal = num2str(NASIG+NDSIG);
	std::string NASIG  = strcat(num2str(NASIG),'A');
	std::string NDSIG  = strcat(num2str(NDSIG),'D');
	//Пишем название регистратора (версия симулинк+релиз)в
	//пустой текстовый файл формата .cfg:
	std::string c_Path = "D:\\work\\";
	std::string FileName_out;
	sprintf(FileName_out, "%s%s_mu.cfg", c_Path, FileName);//s -string, d - double
	out_mu = fopen(FileName_out, "w");

	MatLabVersion=ver('Simulink');
	StationID=strcat(MatLabVersion.Name,'_',MatLabVersion.Version,...
					 MatLabVersion.Release);
	file=fopen(strcat(FileName,'.cfg'),'wt');
	fprintf(file,'%s\n',strcat(StationID , ','  ,'1'));
	fprintf(file,'%s\n',strcat(Ntotal,',',NASIG,',',NDSIG));
	//Записываем в пустой тектовый файл с расширением .cfg
	//информацию по сигналам
	for (int i = 0; i < SIGNALS.size(); i++)
	{
		if (SIGNALS(1,i).SIGTYPE=='A')
		{
			fprintf(file,strcat(num2str(NUM(i,1)) , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGID , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGPH , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGCC , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGUU , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGA , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGB , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGSKEW, ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGMIN), ',');
			fprintf(file,strcat(',',SIGNALS(1,i).SIGMAX));
			fprintf(file,'\n');
		}
		if (SIGNALS(1,i).SIGTYPE=='D')
		{
			fprintf(file,strcat(num2str(NUM(i,1)) , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGID , ','));
			fprintf(file,strcat(SIGNALS(1,i).SIGM));
			fprintf(file,'\n');
		}
	}
	//Частота дискретизации, количество замеров, время и.т.д
	fprintf(file,Fnetwork);%частота сети
	fprintf(file,'\n');
	fprintf(file,'1');//колличество частот дискретизации
	fprintf(file,'\n');
	fprintf(file,strcat(Fsampl,',',Nsampl));//запись значений частоты дискретизации
	fprintf(file,'\n');
	fprintf(file,'19/10/2016,10:41:04.000');//время начала записи
	fprintf(file,'\n');
	fprintf(file,'19/10/2016,10:41:05.000');//время окончания записи
	fprintf(file,'\n');
	fprintf(file,'ASCII');//описание формата
	fclose('all');//закрываем все файлы
}

void Comtrade::DatFilePrint(float* SIGNALS,float Time,std::string FileName)
{
	dlmwrite(strcat(FileName,'.dat'),'');

	if (nargin>0)
	wdt  = length(SIGNALS);
	lng  = length(SIGNALS(1).SIGDATA);
	Data = zeros(lng, wdt);

	for i=1:wdt
		Data(:,i) = SIGNALS(i).SIGDATA;
	end

	Number = transpose(1:lng);

	datfile = [Number, Time, Data];

	format = '';
	n = 1;

	for (int i = 1; i < wdt+2; i++)
	{
		if (i==wdt+2 && SIGNALS(n).SIGTYPE == 'A')
		{
			format = strcat(format,'%.6f','\n');
		}

		if (i==wdt+2 && SIGNALS(n).SIGTYPE == 'D')
		{
			format = strcat(format,'%.0f','\n');
		}

		if (i==1)
		{
		format = strcat(format,'%.0f',',');
		}

		if (i==2)
		{
			format = strcat(format,'%.0f',',');
		}

		if i>2 && i < wdt+2 && n < wdt
		{
			if SIGNALS(n).SIGTYPE == 'A'
			{
				format = strcat(format,'%.6f',',');
				n = n + 1;
			}

			if (SIGNALS(n).SIGTYPE == 'D')
			{
				format = strcat(format,'%.0f',',');
				n = n + 1;
			}
		}


	file = fopen(strcat(FileName,'.dat'),'wt');
	fprintf(file, format, transpose(datfile));
	fclose('all');
}

void Comtrade::COMTRADEFORM(std::string FileName , std::string VoltageUnits , std::string CurrentUnits , float SIGA , float SIGB , std::string BusCreatorName , float* DAT)
{
	ModelName = bdroot(gcb);
	directory=strcat(ModelName,'/',BusCreatorName);
	SigNames_cell    =get_param(directory,'InputSignalNames');
	SigNames		 =string(SigNames_cell);
	SigNames_char    =char(SigNames_cell);

	//Атрибуты сигналов:
	SigTypes=zeros(1,1);%тип сигнала (дискрет/аналог)
	SigUnits=zeros(1,4);%единицы измерения сигнала В/А
	SigPh   =zeros(1,1);%фаза сигнала (А,В,С)
	[lng, wdt] = size(DAT);

	for (int i = 1; i < wdt; i++)
	{
		//Узнаем тип сигнала:
		if (SigNames_char(i,1)=='_')
		{SigTypes(i,1) = 'D';}
		else
		{SigTypes(i,1) = 'A';}

		//Узнаем единицы измерения сигнала(только для аналогов!)
		if (SigTypes(i,1)=='A' && SigNames_char(i,1)=='U')
		{SigUnits(i,1:length(VoltageUnits))=VoltageUnits;}
		else{
			if (SigTypes(i,1)=='A' && SigNames_char(i,1)=='I')
			{SigUnits(i,1:length(CurrentUnits))=CurrentUnits;}
			else
			{SigUnits(i,:)=' ';}
		}

		%Узнаем фазу сигнала (только для аналогов!)
		if (SigTypes(i,1)=='A' && SigNames_char(i,2)=='a' && (SigNames_char(i,1)=='U' || SigNames_char(i,1)=='I'))
		{SigPh(i,1)='A';}
		else
			if (SigTypes(i,1)=='A' && SigNames_char(i,2)=='b')
			{SigPh(i,1)='B';}
			else
				if (SigTypes(i,1)=='A' && SigNames_char(i,2)=='c')
				{SigPh(i,1)='C';}
				else{SigPh(i,1)=' ';}
	}

	SigTypes=char(SigTypes);
	SigUnits=char(SigUnits);
	SigPh   =char(SigPh);
	//Signal(SIGID,SIGPH,SIGCC,SIGUU,SIGA,SIGB,SIGSKEW,SIGM,SIGTYPE,SIGDATA,TIME)
	TIME=DAT(:,1);
	SIG=Signal(' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ');

	for (int i = 1; i < wdt; i++)
	{
		if (SigTypes(i,:)=='A')
		{SIG(1,i)=Signal(SigNames(1,i) , SigPh(i,:) , ' ' , SigUnits(i,:) , SIGA , SIGB ,'0','0','A',DAT(:,i),TIME);}

		if (SigTypes(i,:)=='D' && DAT(1,i)==0)
		{SIG(1,i)=Signal(SigNames(1,i) , SigPh(i,:) , ' ' , SigUnits(i,:) , '1' , '0' , '0' , '0' , 'D',DAT(:,i),TIME);}

		if (SigTypes(i,:)=='D' && DAT(1,i)==1)
		{SIG(1,i)=Signal(SigNames(1,i),SigPh(i,:),' ',SigUnits(i,:),'1','0','0','1','D',DAT(:,i),TIME);}
	}
	SIG(:,1)=[];//Удяляем первый столбец, т.к. это время
	COMTRADE(50,FileName,SIG);
}

*/
