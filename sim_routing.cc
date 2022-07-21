#include "sim_router.h"
#include "sim_foundation.h"
#include "mess_queue.h"
#include "mess_event.h"
#include "SRGen.h"
#include "SStd.h"
#include<iostream>


//***************************************************************************//

void sim_router_template::Adaptive_TM_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long xoffset = des_t[0] - address_[0];
	long yoffset = des_t[1] - address_[1];

    //cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")"<<"   " output_module_.counters(p)
    //<<"current("<<address_[0]<<","<<address_[1]<<")"<<endl;
	//y<0 p3, y>0 p4, x<0 p1, x>0 p2

	
	if(xoffset==0) //x方向不需要移动
	{
		if(yoffset<0) //yoffset<0,往端口3方向传输
		  input_module_.add_routing(s_ph, s_vc, VC_type(3, 0));
		  
		else  //yoffset<=0,往端口4方向传输
		  input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
	}
    if(yoffset==0)  //y方向不需要移动
	{
		if(xoffset<0)  //xoffset<0,往端口1方向传输
		  input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));
		else  //xoffset>=0,往端口2方向传输
		  input_module_.add_routing(s_ph, s_vc, VC_type(2, 0));
	}
	if(yoffset < 0&&xoffset < 0) 
	{
		if(output_module_.counter(3,0) > output_module_.counter(1,0))
		  input_module_.add_routing(s_ph, s_vc, VC_type(3, 0));
		else
		  input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));	
	}

	if(yoffset < 0&&xoffset > 0) 
	{
		//  if(output_module_.counter(3,0) > output_module_.counter(2,0))
		//    input_module_.add_routings(s_ph, s_vc, 3);	
		//  else
		//不进行路径比较，只向x方向(即端口2方向)进行路由
		  input_module_.add_routing(s_ph, s_vc, VC_type(2, 0));
	}

	if(yoffset > 0&&xoffset < 0) //左下
	{
		 if(output_module_.counter(4,0) > output_module_.counter(1,0))
		  input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
		 else
		  input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));
	}

	if(yoffset > 0&&xoffset > 0) 
	{
		if(output_module_.counter(4,0) > output_module_.counter(2,0))
		  input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
		else
		  input_module_.add_routing(s_ph, s_vc, VC_type(2, 0));	
	}

}

void sim_router_template::Adaptive_VN_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long xoffset = des_t[0] - address_[0];
	long yoffset = des_t[1] - address_[1];

    //cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")"<<"   " output_module_.counters(p)
    //<<"current("<<address_[0]<<","<<address_[1]<<")"<<endl;
	//y<0 p3, y>0 p4, x<0 p1, x>0 p2

	
	if(xoffset==0)  //x方向不需要移动
	{
		if(yoffset<0)  //yoffset<0,往端口3方向传输,开放通道2
		  input_module_.add_routing(s_ph, s_vc, VC_type(3, 2));
		else  //yoffset>=0,往端口4方向传输,开放通道3
		  input_module_.add_routing(s_ph, s_vc, VC_type(4, 3));
	}
    if(yoffset==0)  //y方向不需要移动
	{
		if(xoffset<0)  //xoffset<0,往端口1方向传输,开放通道0
		  input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));
		else  //xoffset>=0,往端口2方向传输,开放通道1
		  input_module_.add_routing(s_ph, s_vc, VC_type(2, 1));
	}
	if(yoffset < 0&&xoffset < 0) 
	{
		//counter(3)大则选择端口3进行路由
		if(output_module_.counter(3,2) > output_module_.counter(1,0))
		  input_module_.add_routing(s_ph, s_vc, VC_type(3, 2));
		else	
		  input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));
	}

	if(yoffset < 0&&xoffset > 0) //右上
	{
		 if(output_module_.counter(3,2) > output_module_.counter(2,1))
		   input_module_.add_routing(s_ph, s_vc, VC_type(3, 2));	
		 else
		  input_module_.add_routing(s_ph, s_vc, VC_type(2, 1));	
	}

	if(yoffset > 0&&xoffset < 0) //左下
	{
		 if(output_module_.counter(4,3) > output_module_.counter(1,0))
		  input_module_.add_routing(s_ph, s_vc, VC_type(4, 3));
		 else
		  input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));	
	}

	if(yoffset > 0&&xoffset > 0) 
	{
		if(output_module_.counter(4,3) > output_module_.counter(2,1))
		  input_module_.add_routing(s_ph, s_vc, VC_type(4, 3));
		else	
		  input_module_.add_routing(s_ph, s_vc, VC_type(2, 1));
	}

}
//***************************************************************************/
void sim_router_template::TXY_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long xoffset = des_t[0] - address_[0];
	long yoffset = des_t[1] - address_[1];
    //cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")"<<"   "
    //<<"current("<<address_[0]<<","<<address_[1]<<")"<<endl;
    

	bool xdirection = (abs(static_cast<int>(xoffset)) * 2 //true时不反向经过长线
					<= ary_size_)? true: false; 
	bool ydirection = (abs(static_cast<int>(yoffset)) * 2
					<= ary_size_)? true: false; 
/*
if(xdirection) {
		if(xoffset < 0) {
			//input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));
			input_module_.add_routings(s_ph, s_vc, (long)1);

		}else if(xoffset > 0) {
			//input_module_.add_routing(s_ph, s_vc, VC_type(2, 1));
			input_module_.add_routings(s_ph, s_vc, (long)2);
			
		}else {
			if(ydirection) {
				if(yoffset < 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(3, 0));
					input_module_.add_routings(s_ph, s_vc, (long)3);
				}else if(yoffset > 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(4, 1));
					input_module_.add_routings(s_ph, s_vc, (long)4);
				}
			}else {
				if(yoffset < 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
					input_module_.add_routings(s_ph, s_vc, (long)4);
				}else if(yoffset > 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(3, 1)); 
					input_module_.add_routings(s_ph, s_vc, (long)3);
				}
			}
		}
	}else  {
		if(xoffset < 0) {
			//input_module_.add_routing(s_ph, s_vc, VC_type(2, 0));
			input_module_.add_routings(s_ph, s_vc, (long)2);
		}else if(xoffset > 0) {
			//input_module_.add_routing(s_ph, s_vc, VC_type(1, 1));
		    input_module_.add_routings(s_ph, s_vc, (long)1);
		}else {
			if(ydirection) {
				if(yoffset < 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(3, 0));
					input_module_.add_routings(s_ph, s_vc, (long)3);
				}else if(yoffset > 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(4, 1));
					input_module_.add_routings(s_ph, s_vc, (long)4);
				}
			}else {
				if(yoffset < 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
					input_module_.add_routings(s_ph, s_vc, (long)4);
				}else if(yoffset> 0) {
					//input_module_.add_routing(s_ph, s_vc, VC_type(3, 1));
					input_module_.add_routings(s_ph, s_vc, (long)3); 
				}
			}
		}
	}
*/
	if(xdirection) {
		if(xoffset < 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(1, 0));
		}else if(xoffset > 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(2, 1));
		}else {
			if(ydirection) {
				if(yoffset < 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(3, 0));
				}else if(yoffset > 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(4, 1));
				}
			}else {
				if(yoffset < 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
				}else if(yoffset > 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(3, 1)); 
				}
			}
		}
	}else  {
		if(xoffset < 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(2, 0));
		}else if(xoffset > 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(1, 1));
		}else {
			if(ydirection) {
				if(yoffset < 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(3, 0));
				}else if(yoffset > 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(4, 1));
				}
			}else {
				if(yoffset < 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(4, 0));
				}else if(yoffset> 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(3, 1)); 
				}
			}
		}
	}



}

//***************************************************************************//
void sim_router_template::XY_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long xoffset = des_t[0] - address_[0];
	long yoffset = des_t[1] - address_[1];

    //cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")"<<"   "
    //<<"current("<<address_[0]<<","<<address_[1]<<")"<<endl;

	if(yoffset < 0) {
		input_module_.add_routing(s_ph, s_vc, VC_type(3,0));
		input_module_.add_routing(s_ph, s_vc, VC_type(3,1));
		input_module_.add_routing(s_ph, s_vc, VC_type(3,2));
		input_module_.add_routing(s_ph, s_vc, VC_type(3,3));
	}else if(yoffset > 0) {
		input_module_.add_routing(s_ph, s_vc, VC_type(4,0));
		input_module_.add_routing(s_ph, s_vc, VC_type(4,1));
		input_module_.add_routing(s_ph, s_vc, VC_type(4,2));
		input_module_.add_routing(s_ph, s_vc, VC_type(4,3));
	}else {
		if(xoffset < 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(1,0));
			input_module_.add_routing(s_ph, s_vc, VC_type(1,1));
			input_module_.add_routing(s_ph, s_vc, VC_type(1,2));
			input_module_.add_routing(s_ph, s_vc, VC_type(1,3));
		}else if (xoffset > 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(2,0));
			input_module_.add_routing(s_ph, s_vc, VC_type(2,1));
			input_module_.add_routing(s_ph, s_vc, VC_type(2,2));
			input_module_.add_routing(s_ph, s_vc, VC_type(2,3));
		}
	}
}

void sim_router_template::XYZ_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long xoffset = des_t[0]-address_[0];
	long yoffset = des_t[1]-address_[1];
	long zoffset = des_t[2]-address_[2];
	if(zoffset < 0)
	{
		input_module_.add_routing(s_ph, s_vc, VC_type(5,0));
		input_module_.add_routing(s_ph, s_vc, VC_type(5,1));
		input_module_.add_routing(s_ph, s_vc, VC_type(5,2));
		input_module_.add_routing(s_ph, s_vc, VC_type(5,3));
	}
	else if(zoffset > 0)
	{
		input_module_.add_routing(s_ph, s_vc, VC_type(6,0));
		input_module_.add_routing(s_ph, s_vc, VC_type(6,1));
		input_module_.add_routing(s_ph, s_vc, VC_type(6,2));
		input_module_.add_routing(s_ph, s_vc, VC_type(6,3));
	}
	else
	{
		if(yoffset < 0) 
		{
			input_module_.add_routing(s_ph, s_vc, VC_type(3,0));
			input_module_.add_routing(s_ph, s_vc, VC_type(3,1));
			input_module_.add_routing(s_ph, s_vc, VC_type(3,2));
			input_module_.add_routing(s_ph, s_vc, VC_type(3,3));
		}
		else if(yoffset > 0) 
		{
			input_module_.add_routing(s_ph, s_vc, VC_type(4,0));
			input_module_.add_routing(s_ph, s_vc, VC_type(4,1));
			input_module_.add_routing(s_ph, s_vc, VC_type(4,2));
			input_module_.add_routing(s_ph, s_vc, VC_type(4,3));
		}
		else 
		{
			if(xoffset < 0) 
			{
				input_module_.add_routing(s_ph, s_vc, VC_type(1,0));
				input_module_.add_routing(s_ph, s_vc, VC_type(1,1));
				input_module_.add_routing(s_ph, s_vc, VC_type(1,2));
				input_module_.add_routing(s_ph, s_vc, VC_type(1,3));
			}
			else if (xoffset > 0) 
			{
				input_module_.add_routing(s_ph, s_vc, VC_type(2,0));
				input_module_.add_routing(s_ph, s_vc, VC_type(2,1));
				input_module_.add_routing(s_ph, s_vc, VC_type(2,2));
				input_module_.add_routing(s_ph, s_vc, VC_type(2,3));
			}
		}
	}
}
			
//***************************************************************************//
//only two-dimension is supported
void sim_router_template::routing_decision()
{
	time_type event_time = mess_queue::m_pointer().current_time();

	//for injection physical port 0
	for(long j = 0; j < vc_number_; j++) {
		//for the HEADER_ flit
		flit_template flit_t;
		if(input_module_.state(0,j) == ROUTING_) {
			flit_t = input_module_.get_flit(0,j);
			add_type des_t = flit_t.des_addr();
			add_type sor_t = flit_t.sor_addr();

			if(configuration::ap().cube_number()==2)  //二维网络的节点信息打印  
              cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")->("<<des_t[0]<<","<<des_t[1]<<")  "<<"injected      ";
			
			if(configuration::ap().cube_number()==3)  //三维网络的节点信息打印  
              cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<","<<sor_t[2]
			  <<")->("<<des_t[0]<<","<<des_t[1]<<","<<des_t[2]<<")  "<<"injected      ";

			// for(long p = 1; p < physic_ports_; p++) 
		    //    if(configuration::ap().routing_alg()==2)
			// 		cout<<output_module_.counter(p,p-1)<<' ';
			// 	else if(configuration::ap().routing_alg()==3)					
			// 		cout<<output_module_.counters(p)<<' ';
			cout<<endl;

			if(address_ == des_t) {
				accept_flit(event_time, flit_t);
				input_module_.remove_flit(0, j);
				input_module_.state_update(0, j, HOME_);
			}else {
				input_module_.clear_routing(0,j);
				input_module_.clear_crouting(0,j);
				(this->*curr_algorithm)(des_t, sor_t, 0, j);
				input_module_.state_update(0, j, VC_AB_);
			}
		//the BODY_ or TAIL_ flits
		}else if(input_module_.state(0,j) == HOME_)  {
			if(input_module_.input(0, j).size() > 0) {
				flit_t = input_module_.get_flit(0, j);
				Sassert(flit_t.type() != HEADER_);
				accept_flit(event_time, flit_t);
				input_module_.remove_flit(0, j);
				if(flit_t.type() == TAIL_) {
					if(input_module_.input(0, j).size() > 0) {
						input_module_.state_update(0, j, ROUTING_);
					}else {
						input_module_.state_update(0, j, INIT_);
					}
				}
			}
		}
	}

	//for other physical ports
	for(long i = 1; i < physic_ports_; i++) {
		for(long j = 0; j < vc_number_; j++) {
			//send back CREDIT message
			flit_template flit_t;
			if(input_module_.input(i,j).size() > 0) {
				flit_t = input_module_.get_flit(i,j);
				add_type des_t = flit_t.des_addr();

				if(address_ == des_t) {
					add_type cre_add_t = address_;
					long cre_pc_t = i;
					if((i % 2) == 0) {
						cre_pc_t = i - 1;
						cre_add_t[(i-1)/2] ++;
						if(cre_add_t[(i-1)/2] == ary_size_) {
							cre_add_t[(i-1)/2] = 0;
						}
					}else {
						cre_pc_t = i + 1;
						cre_add_t[(i-1)/2] --;
						if(cre_add_t[(i-1)/2] == -1) {
							cre_add_t[(i-1)/2] = ary_size_ - 1;
						}
					}
					mess_queue::wm_pointer().add_message(
						mess_event(event_time + CREDIT_DELAY_, 
						CREDIT_, address_, cre_add_t, cre_pc_t, j));
				}
			}
			//for HEADER_ flit
			if(input_module_.state(i, j) == ROUTING_) {
				flit_t = input_module_.get_flit(i, j);
				Sassert(flit_t.type() == HEADER_);
				add_type des_t = flit_t.des_addr();
				add_type sor_t = flit_t.sor_addr();
				if(address_ == des_t) {  //若数据包到达目标节点，打印终点信息
					accept_flit(event_time, flit_t);
					input_module_.remove_flit(i, j);
					input_module_.state_update(i, j, HOME_);

					if(configuration::ap().cube_number()==2) //二维网络的节点信息打印  
                       cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")"<<"         "
                    <<"destination("<<address_[0]<<","<<address_[1]<<")"<<endl;
			
			        if(configuration::ap().cube_number()==3) //三维网络的节点信息打印  
				       cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<","<<sor_t[2]<<")"<<"         "
                    <<"destination("<<address_[0]<<","<<address_[1]<<","<<address_[2]<<")"<<endl;

				}else {  //若数据包未到达目标节点，打印当前节点信息
					input_module_.clear_routing(i, j);
					input_module_.clear_crouting(i, j);
					(this->*curr_algorithm)(des_t, sor_t, i, j);
					input_module_.state_update(i, j, VC_AB_);

					if(configuration::ap().cube_number()==2)  //二维网络的节点信息打印 
					  cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<")->("<<des_t[0]<<","<<des_t[1]<<")  "
                    <<"current("<<address_[0]<<","<<address_[1]<<")  ";

					if(configuration::ap().cube_number()==3)  //三维网络的节点信息打印 
					  cout<<"source ("<<sor_t[0]<<","<<sor_t[1]<<","<<sor_t[2]<<")->("<<des_t[0]<<","<<des_t[1]<<","<<des_t[2]<<")  "
                    <<"current("<<address_[0]<<","<<address_[1]<<","<<address_[2]<<")  ";

					for(long p = 1; p < physic_ports_; p++) 
		               //for(long c = 0; c < vc_number_; c++)
					   if(configuration::ap().routing_alg()==2) //Virtual Network的路径信息打印
					      cout<<output_module_.counter(p,p-1)<<' ';
						else if(configuration::ap().routing_alg()==3) //Turn Model的路径信息打印
						cout<<output_module_.counter(p,0)<<' ';
					cout<<endl;
					   
				}
			//for BODY_ or TAIL_ flits
			}else if(input_module_.state(i, j) == HOME_) {
				if(input_module_.input(i, j).size() > 0) {
					flit_t = input_module_.get_flit(i, j);
					Sassert(flit_t.type() != HEADER_);
					accept_flit(event_time, flit_t);
					input_module_.remove_flit(i, j);
					if(flit_t.type() == TAIL_) {
						if(input_module_.input(i, j).size() > 0) {
							input_module_.state_update(i, j, ROUTING_);
						}else {
							input_module_.state_update(i, j, INIT_);
						}
					}
				}
			}
		}
	}
}

//***************************************************************************//
