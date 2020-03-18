/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mvc.libInterpreteurExpr;

public class Node {

	// Variables
	
		int mOperator;
		double mValue;
		Node fg, fd;
	
	// Methods
	
	//.................................................................................... Node
	
	public Node() {
	fg=null;
	fd=null;
	}
	
	//.................................................................................... Node
	
	public Node(int Operator,double Value,Node Fg,Node Fd) {
	mOperator=Operator;
	mValue=Value;
	fg=Fg;
	fd=Fd;
	}
	
	public Node(int Operator,double Value) {
	mOperator=Operator;
	mValue=Value;
	fg=null;
	fd=null;
	}
	
	//.................................................................................... Construct_Tree
	
	public static Node  Construct_Tree(StringBuffer string,int length,int  error) {
	int imbric,Bimbric;
	int priorite,ope;
	int position,positionv,i,j;
	int opetemp=0;
	int espa=0,espat=0;
	int caspp=0;

	Node  node;

	// Initialisation des variables

	if (length<=0) {
		error=3;
		return null;
	}

	ope=0;
	imbric=0;Bimbric=128;
	priorite=6;
	i=0;
	positionv=position=0;

	// Mise en place des donnees sur le morceau de chaine

	while (i<length) {
		
		if (((string.charAt(i)>47) && (string.charAt(i)<58)) || (string.charAt(i)=='ž')) {
			if (priorite>5) {
				priorite=5;
				positionv=i;
			}
			i++;
		}
		else {
		if ((string.charAt(i)>96) && (string.charAt(i)<117)) {
			VariableInt Vopetemp,Vespat;
			
			Vopetemp= new VariableInt();
			Vespat= new VariableInt();
			
			Vopetemp.mValue=opetemp;
			Vespat.mValue=espat;
			
			FindOperator(Vopetemp,Vespat,string,i);
			
			opetemp=Vopetemp.mValue;
			espat=Vespat.mValue;
			
			if (opetemp>=0) {
				if (imbric<Bimbric) {
					Bimbric=imbric;
					ope=opetemp;
					position=i;
					priorite=4;
					espa=espat;
				} 
				else if ((imbric==Bimbric) && (priorite >=4)) {
					ope=opetemp;
					position=i;
					priorite=4;
					espa=espat;
				}
				j=i+1;
				i+=espat;
				while(j<i) 
					j++;
				
			}
			else if (string.charAt(i)=='t') {
				if (priorite==6) ope=-1;
				i++;
			}
			else if (string.charAt(i)=='p') {
				if (priorite==6) ope=-2;
				i++;
			}
			else if (string.charAt(i)=='r') {
				if (priorite==6) ope=-2;
				i++;
			}
			else if (string.charAt(i)=='n') {
				if (priorite==6) ope=-1;
				i++;
			}
			else {
				error=2; // symbole non reconnu
	            return null;
	        }
		}
		else {
			switch(string.charAt(i)) {
				case '(':
					imbric++;
					i++;
					break;
				case ')':
					imbric--;
					i++;
					break;
				case '+':
					if (imbric<Bimbric) {
						Bimbric=imbric;
						priorite=1;
						ope=1;
						position=i;
						caspp=0;
					}
					else if ((imbric==Bimbric) && (priorite >=1)) {
						priorite=1;
						ope=1;
						position=i;
						caspp=0;
					}
					i++;
					break;
				case '-':
					if (imbric<Bimbric) {
						if ((i-1)<0) {
							if (priorite>5) {
								priorite=1;
								position=i;
								ope=2;
								Bimbric=imbric;
								caspp=1;
							}
						}
					 	else if (string.charAt(i-1)=='(') {
					 		if (priorite>1){
					 			priorite=1;
					 			position=i;
					 			Bimbric=imbric;
					 			caspp=1;
					 			ope=2;
					 		}
					 	}
						else {
							Bimbric=imbric;
							priorite=1;
							ope=2;
							position=i;
							caspp=0;
						}
					}
					else if ((imbric==Bimbric) && (priorite>=1)) {
						if ((i-1)<0) {
							if (priorite>5) {
								priorite=1;
								position=i;
								ope=2;
								caspp=1;
							}
						}
						else if (string.charAt(i-1)=='(') {
							if (priorite>1){
								priorite=1;
								position=i;
								caspp=1;
								ope=2;
							}
						}
						else {
							priorite=1;
							ope=2;
							position=i;
							caspp=0;
						}
					}
					i++;
					break;
				case '*':
					if (imbric<Bimbric) {
						Bimbric=imbric;
						priorite=2;
						ope=3;
						position=i;
					}
					else if ((imbric==Bimbric) && (priorite>=2)) {
						priorite=2;
						ope=3;
						position=i;
					}
					i++;
					break;
				case '/':
					if (imbric<Bimbric) {
						Bimbric=imbric;
						priorite=2;
						ope=4;
						position=i;
					}
					else if ((imbric==Bimbric) && (priorite>=2)) {
						priorite=2;
						ope=4;
						position=i;
					}
					i++;
					break;
				case '^':
					if (imbric<Bimbric) {
						Bimbric=imbric;
						priorite=3;
						ope=5;
						position=i;
					}
					else if ((imbric==Bimbric) && (priorite>=3)) {
						priorite=3;
						ope=5;
						position=i;
					}
					i++;
					break;
				case '.':
					i++;
					break;
				case 'x':
					if (priorite==6) ope=-1;
					i++;
					break;
				case 'y':
					if (priorite==6) ope=-2;
					i++;
					break;
				default:
					error=2; // symbole non reconnu
					return null;
				}
			}
		}
	}

	if (imbric!=0) {
		error=1; // erreur de "parenthesage"
		return null;
	}

	// Traitement des donnees	

	if (priorite==6) {
		node =new Node(ope,0.0);
		return node;
	}
	else if (caspp==1) {
		node = new Node(2,0);
		
		node.fg= new Node(0,0);
		node.fd= new Node();
					    
		if ((length-position-1-Bimbric)==0) { // argument absent
			error=3;
			return null;
			} 
		StringBuffer temp=CopyPartialString(string,(position+1),(length-1-Bimbric));
		node.fd=Construct_Tree(temp,(length-position-1-Bimbric),error);
		
		return node;
		}

	else if (priorite==5) {
		node = new Node(0,calc_const(string,positionv),null,null);
		
		return node;
	}
	else if (ope>5) {
		node = new Node(ope,0,null,null);
		
		if ((length-position-espa-Bimbric)==0) { // argument absent
			error=3;
			return null;
		}
		StringBuffer temp=CopyPartialString(string,(position+espa),(length-1));
		node.fg=Construct_Tree(temp,(length-position-espa-Bimbric),error);
		return node;
	} 
	else{
		node = new Node(ope,0,null,null);
		
		if ((position-Bimbric)==0) { // argument absent
			error=3;
			return null;
		}
		StringBuffer temp=CopyPartialString(string,Bimbric,(position-1));
		node.fg=Construct_Tree(temp,(position-Bimbric),error);
		if ((length-position-1-Bimbric)==0) { // argument absent
			error=3;
			return null;
		}
		temp=CopyPartialString(string,(position+1),(length-1-Bimbric));
		node.fd=Construct_Tree(temp,(length-position-1-Bimbric),error);
		return node;
	}
	}
	
	//....................................................................................
	
	public double Compute_Tree(double value1,double value2,int error) {
	if (mOperator==0) return mValue;
	if (mOperator==-1) return value1;
	if (mOperator==-2) return value2;

	double valueL=fg.Compute_Tree(value1,value2,error);

	if (error!=0) return 0;
	double valueR=0;

	if (fd!=null) valueR=fd.Compute_Tree(value1,value2,error);
	if (error!=0) return 0;

	switch(mOperator) {
		case 1:								// +
			return (valueL+valueR);
		case 2:								// -
			return (valueL-valueR);
		case 3:								// *
			return (valueL*valueR);
		case 4:								// -
			if (valueR==0) {
				error=1;
				return 0;
			}
			return (valueL/valueR);
		case 5:								// ^
			return Math.pow(valueL,valueR);
		case 6:								// exp
			return Math.exp(valueL);
		case 7:								// ln
			if (valueL<=0) {
				if (valueL<0) error=2;
				else error=1;
				return 0;
			}
			return (Math.log(valueL)/Math.log(2));
		case 8:								// log
			if (valueL<=0) {
				if (valueL<0) error=2;
				else error=1;
				return 0;
			}
			return Math.log(valueL);
		case 9:								// sqrt
			if (valueL<0) {
				error=2;
				return 0;
			}
			return Math.sqrt(valueL);
		case 10:							// abs
			return Math.abs(valueL);
		case 11:
			return Math.sin(valueL);			// sin
		case 12:
			return Math.cos(valueL);			// cos
		case 13:
			return Math.tan(valueL);			// tan
		case 14:
			return Math.asin(valueL);			// asin
		case 15:
			return Math.acos(valueL);			// acos
		case 16:
			return Math.atan(valueL);			// atan
		default:
			return 0;
	}
	}
	
	//.................................................................................... Write_Tree
	
	public void Write_Tree(StringBuffer string) {
	boolean parenthese=false;

	switch(mOperator) {
		case -2:
			string.append('y');
			break;
		case -1:
			string.append('x');
			break;
		case 0:
			string.append(mValue);
			break;
		case 1:
			fg.Write_Tree(string);
			string.append('+');
			fd.Write_Tree(string);
			break;
		case 2:
			if ((fg.mOperator==0) && (fg.mValue==0));
			else fg.Write_Tree(string);
			string.append('-');
			if ((fd.mOperator==1) || (fd.mOperator==2)) {
				parenthese=true;
				string.append('(');
			}
			fd.Write_Tree(string);
			if (parenthese==true) {
				string.append(')');
			}
			break;
		case 3:
			if ((fg.mOperator==1) || (fg.mOperator==2)) {
				parenthese=true;
				string.append('(');
			}
			fg.Write_Tree(string);
			if (parenthese==true)
				string.append(')');
			parenthese=false;
			string.append('*');
			if ((fd.mOperator==1) || (fd.mOperator==2)) {
				parenthese=true;
				string.append('(');
			}
			fd.Write_Tree(string);
			if (parenthese==true)
				string.append(')');
			break;
		case 4:
			if ((fg.mOperator==1) || (fg.mOperator==2)) {
				parenthese=true;
				string.append('(');
			}
			fg.Write_Tree(string);
			if (parenthese==true)
				string.append(')');
			parenthese=false;
			string.append('/');
			if ((fd.mOperator>0) && (fd.mOperator<5)) {
				parenthese=true;
				string.append('(');
			}
			fd.Write_Tree(string);
			if (parenthese==true) 
				string.append(')');
			break;
		case 5:
			if ((fg.mOperator>0) && (fg.mOperator<5)) {
				parenthese=true;
				string.append('(');
			}
			fg.Write_Tree(string);
			if (parenthese==true)
				string.append(')');
			parenthese=false;
			string.append('^');
			if ((fd.mOperator>0) && (fd.mOperator<5)) {
				parenthese=true;
				string.append('(');
			}
			fd.Write_Tree(string);
			if (parenthese==true) 
				string.append(')');
			break;
		case 6:
			string.append("exp(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 7:
			string.append("log(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 8:
			string.append("ln(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 9:
			string.append("Ã(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 10:
			string.append("|");
			fg.Write_Tree(string);
			string.append('|');
			break;
		case 11:
			string.append("sin(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 12:
			string.append("cos(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 13:
			string.append("tan(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 14:
			string.append("asin(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 15:
			string.append("acos(");
			fg.Write_Tree(string);
			string.append(')');
			break;
		case 16:
			string.append("atan(");
			fg.Write_Tree(string);
			string.append(')');
			break;
	}
	}
	
	//.................................................................................... calc_const
	
	static double calc_const(StringBuffer chaine,int pos) {
	int i=pos,j;
	double temp=0;
	int signe=1;
	int longueur=chaine.length();

	
	if (chaine.charAt(i)=='-') {
		signe=-1;
		i++;
	}
	if (chaine.charAt(i)=='ž') return signe*Math.PI;
	
	while (i<longueur && chaine.charAt(i)>47 && chaine.charAt(i)<58) {
		temp=temp*10+(chaine.charAt(i)-48);
		i++;
	}
	if (i<longueur && chaine.charAt(i)=='.') {
		i++;
		j=1;
		while (i<longueur && chaine.charAt(i)>47 && chaine.charAt(i)<58) {
			temp=temp+(chaine.charAt(i)-48)*Math.exp(-j*2.30258509);
			i++;
			j++;
		}
	}
	return (signe*temp);
	}
	
	//.................................................................................... FindOperator
	
	static void FindOperator(VariableInt oper,VariableInt esp,StringBuffer chaine,int pos) {
	switch(chaine.charAt(pos)) {
	case 'a':
		switch(chaine.charAt(pos+1)) {
			case 'b':
				esp.mValue=3;
				oper.mValue=10;
				break;
			case 'c':
				esp.mValue=4;
				oper.mValue=15;
				break;
			case 's':
				esp.mValue=4;
				oper.mValue=14;
				break;
			case 't':
				esp.mValue=4;
				oper.mValue=16;
				break;
		}
		break;
	case 'c':
		if (chaine.charAt(pos+1)=='h') {
			esp.mValue=2;
			oper.mValue=18;
		}
		else if ((chaine.charAt(pos+1)=='o') && (chaine.charAt(pos+2)=='s')) {
			if (chaine.charAt(pos+3)=='h') {
				esp.mValue=4;
				oper.mValue=18;
			}
			else {
         		esp.mValue=3;
				oper.mValue=12;
			}
		}
		break;
	case 'e':
		if ((chaine.charAt(pos+1)=='x') && (chaine.charAt(pos+2)=='p')) {
			esp.mValue=3;
         	oper.mValue=6;
		}
		else oper.mValue=-10;
		break;
	case 'l':
		if (chaine.charAt(pos+1)=='n') {
			esp.mValue=2;
			oper.mValue=7;
		}
		else if ((chaine.charAt(pos+1)=='o') && (chaine.charAt(pos+2)=='g')){
         	esp.mValue=3;
            oper.mValue=8;
         }
         else oper.mValue=-10;
         break;
	case 's':
		if (chaine.charAt(pos+1)=='h') {
			esp.mValue=2;
			oper.mValue=17;
		}
		else if (chaine.charAt(pos+1)=='q') {
			esp.mValue=4;
			oper.mValue=9;
		}
		else {
			if (chaine.charAt(pos+3)=='h') {
				esp.mValue=4;
				oper.mValue=17;
			}
			else {
				esp.mValue=3;
				oper.mValue=11;
			}
		}
		break;
	case 't':
		if (chaine.charAt(pos+1)=='h') {
			esp.mValue=2;
			oper.mValue=19;
		}
		else if ((chaine.charAt(pos+1)=='a') && (chaine.charAt(pos+2)=='n')) {
			if (chaine.charAt(pos+3)=='h') {
				esp.mValue=4;
				oper.mValue=19;
			}
			else {
				esp.mValue=3;
				oper.mValue=13;
			}
		}
		else oper.mValue=-10;
		break;
	default:
		oper.mValue=-10;
		break;
	}
	}
	
	//.................................................................................... CopyPartialString
	
	static StringBuffer CopyPartialString(StringBuffer chaine,int debut,int fin) {
	StringBuffer  chartemp;
	int a=fin-debut+1;
	chartemp=new StringBuffer(a+1);

	for(int i=0;i<a;i++) chartemp.append(chaine.charAt(debut+i));

	return chartemp;
	}
}

