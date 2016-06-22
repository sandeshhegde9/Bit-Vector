#include<stdio.h>
#include<stdlib.h>
struct node
{
	int offset;
	unsigned int a[4];
	struct node *link;
};
typedef struct node* NODE;
//NODE union(NODE [],NODE,int);
NODE insertrear(NODE,NODE);
NODE copynode(NODE,NODE);
void display(NODE);
NODE getNode()
{
	NODE a=(NODE)malloc(sizeof(struct node));
	a->link=NULL;
	a->offset=-1;
	int i;
	for(i=0;i<4;i++)
		a->a[i]=0;
	return a;
}

NODE copynode(NODE temp,NODE temp1)
{
	int i;
	temp=getNode();
	temp->offset=temp1->offset;
	for(i=0;i<4;i++)
		temp->a[i]=temp1->a[i];
	temp->link=NULL;
	return temp;
}

NODE copylist(NODE un,NODE temp)
{
	while(temp!=NULL)
	{
		NODE temp1;
		temp1=copynode(temp1,temp);
		un=insertrear(un,temp1);
		temp=temp->link;
	}
	return un;
}

NODE unionn(NODE heads[],NODE un,int n)
{
	int i,j,flag=1;
	NODE temp=getNode(),temp2=NULL,temp1;
	un=copylist(un,heads[0]);
/*	while(temp1!=NULL)
	{
		temp=copynode(temp,temp1);
		un=insertrear(un,temp);
		temp1=temp1->link;
	}*/
	for(i=1;i<n;i++)
	{
		temp1=heads[i];
		while(temp1!=NULL)
		{
			flag=1;
			temp2=un;
			while(temp2!=NULL)
			{
				if(temp2->offset==temp1->offset)
				{
					for(j=0;j<4;j++)
					{
					//	printf("%d   ",temp2->a[j]);
						temp2->a[j]=temp2->a[j]|temp1->a[j];
					}
					flag=0;
				//	printf("\n");
					
				}
				temp2=temp2->link;
			}
			if(flag)
			{
				temp=copynode(temp,temp1);
				un=insertrear(un,temp);
			//	printf("%d  ",temp->a[i]);

			}
			temp1=temp1->link;
		}
	}
	return un;
}

NODE intersection(NODE heads[],NODE un,int n)
{
	int i,j,flag=1;
	NODE temp,temp2=NULL,temp1,un1=NULL;
	un=copylist(un,heads[0]);
/*	while(temp1!=NULL)
	{
		temp=copynode(temp,temp1);
		un=insertrear(un,temp);
		temp1=temp1->link;
	}*/
	for(i=1;i<n;i++)
	{
		temp1=heads[i];
		while(temp1!=NULL)
		{
		//	flag=1;
			temp2=un;
			while(temp2!=NULL)
			{
				if(temp2->offset==temp1->offset)
				{
					for(j=0;j<4;j++)
					{
					//	printf("%d   ",temp2->a[j]);
						temp2->a[j]=temp2->a[j]&temp1->a[j];
					}
				//	flag=0;
				//	printf("\n");
					temp=copynode(temp,temp2);
					un1=insertrear(un1,temp);
				}
				temp2=temp2->link;
			}
			/*if(flag)
			{
				temp=copynode(temp,temp1);
				un=insertrear(un,temp);
			//	printf("%d  ",temp->a[i]);

			}*/
		//	if(un1!=NULL){
		//	un=un1;
		//	display(un);
		//	un1=NULL;}
			temp1=temp1->link;
		}
	}
	return un1;
}

void bitset(NODE node,int item)
{
	int pos,n;
	n=((item-node->offset))/32;
	pos=item%32;
	node->a[n]=node->a[n]|(1<<(pos));
//	printf("%d %d %u\n",n,pos,node->a[n]);
}

NODE search(NODE head,int item)
{
	if(head==NULL)
	{
		return NULL;
	}
	do
	{
		if(head->offset==(item/128)*128)
		{
			return head;
		}
		head=head->link;
	}while(head!=NULL);
	return NULL;
}

NODE insertrear(NODE head,NODE temp)
{
	NODE temp1=head;
	if(temp1==NULL)
	{
		return temp;
	}
	while(temp1->link!=NULL)
	{
		temp1=temp1->link;
	}
	temp->link=NULL;
	temp1->link=temp;
	return head;
}

NODE insert(NODE head,int item)
{
	int o,pos,n;
	NODE temp;
	if(head==NULL)
	{
		head=getNode();
		head->offset=(item/128)*128;
		bitset(head,item);
		return head;
	}
	else
	{
		o=item/128;
		o=o*128;
		temp=search(head,o);
		if(temp!=NULL)
		{
			bitset(temp,item);
			return head;
		}
		else
		{
			temp=getNode();
			temp->offset=(item/128)*128;
			bitset(temp,item);
			head=insertrear(head,temp);
			return head;
		}
	}
}

/*void disp(NODE un)
{
	int i;
	while(un!=NULL)
	{
		for(i=0;i<4;i++)
			printf("%d  ",un->a[i]);
		printf("\n");
		un=un->link;
	}
}*/

void display(NODE head)
{
	int i,count,value;
	while(head!=NULL)
	{
		for(i=0;i<4;i++)
		{
			count=0;
			while(head->a[i]>0)
			{
				if(head->a[i]%2==1)
				{
					value=head->offset+32*i+count;
					printf("%d ",value);
				}
				head->a[i]=head->a[i]>>1;
				count++;
			}
		}	
		head=head->link;
	}
}
void main()
{
	int n,m;
	scanf("%d",&n);
	NODE heads[n],un=getNode(),inter=getNode();
//	NODE union(NODE [],NODE,int);
	int b[100],i,j;
	for(i=0;i<n;i++)
		heads[i]=getNode();
	for(i=0;i<n;i++)
	{
		scanf("%d",&m);
		for(j=0;j<m;j++)
		{
			scanf("%d",&b[j]);
			heads[i]=insert(heads[i],b[j]);
		}
	}
	un=unionn(heads,un,n);
//	disp(un);
	inter=intersection(heads,inter,n);
//	disp(inter);
	display(un);
	printf("\n");
	display(inter);
}
