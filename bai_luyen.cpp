#include<bits/stdc++.h>
using namespace std;
 
class xe{
	private:
		string maXe;
		string loaiXe;
		int gioVao;
		int tgDo;
		double phiDo;
		
	public:
		xe(){
			maXe = "";
			loaiXe = "Car";
			gioVao = 0;
			tgDo = 0;
			phiDo = 0;
		}
		xe(string maXe,string loaiXe, int gioVao, int tgDo, double phiDo){
			this->maXe = maXe;
			this->loaiXe = loaiXe;
			this->gioVao = gioVao;
			this->tgDo = tgDo;
			this->phiDo = phiDo;
		}
		string get_maXe() const{
			return maXe;
		}
		string get_loaiXe() const{
		return loaiXe;
		}
		int get_gioVao()const{
		return gioVao;}
		int get_tgDo()const{
		return tgDo;}
		double get_phiDo(){
			return tinhPhi();
		}
		
		void set_maXe(const string& maXe){
			this->maXe = maXe;
		}
		void set_loaiXe(const string& loaiXe){
			this->loaiXe = loaiXe;
		}
		void set_gioVao(int gioVao){
			this->gioVao = gioVao;
		}
		void set_tgDo(int tgDo){
			this->tgDo = tgDo;
		}
		void set_phiDo(double phiDo){
			this->phiDo = phiDo;
		}
		
		double tinhPhi() const{
			double gia = (loaiXe == "Car")?6: (loaiXe == "Motorcycle")? 4:2;
			double haiGioDau ;
			if(((gioVao>=6)&&(gioVao<=10))||(gioVao>=15&&gioVao<=19)){
				haiGioDau = 2*gia*1.3;
			}
			else
				haiGioDau = 2*gia*0.95;
			
			double tong;
			if(tgDo>2){
				tong = haiGioDau+(tgDo-2)*0.9;
			}
			else
			tong = haiGioDau;
			return tong;
		}
		
		
};
