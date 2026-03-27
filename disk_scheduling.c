#include <stdio.h>
#include <stdlib.h>

int n, h, r[100], d;

void s(int a[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(a[i]>a[j]){int t=a[i];a[i]=a[j];a[j]=t;}
}

void SSTF(){
    int v[100]={0}, t=0, p=h;
    printf("\nSeek Sequence: %d", p);
    for(int i=0;i<n;i++){
        int m=9999,x=-1;
        for(int j=0;j<n;j++)
            if(!v[j] && abs(p-r[j])<m) m=abs(p-r[j]),x=j;
        v[x]=1; t+=m; p=r[x];
        printf(" -> %d", p);
    }
    printf("\nTotal Seek Time = %d\n", t);
}

void LOOK(){
    int l[100], rt[100], lc=0, rc=0, t=0, p=h;
    for(int i=0;i<n;i++)
        (r[i]<h?l[lc++]:rt[rc++])=r[i];
    s(l,lc); s(rt,rc);

    printf("\nSeek Sequence: %d", p);
    if(d==2){
        for(int i=0;i<rc;i++) t+=abs(p-rt[i]), p=rt[i], printf(" -> %d", p);
        for(int i=lc-1;i>=0;i--) t+=abs(p-l[i]), p=l[i], printf(" -> %d", p);
    } else {
        for(int i=lc-1;i>=0;i--) t+=abs(p-l[i]), p=l[i], printf(" -> %d", p);
        for(int i=0;i<rc;i++) t+=abs(p-rt[i]), p=rt[i], printf(" -> %d", p);
    }
    printf("\nTotal Seek Time = %d\n", t);
}

void CSCAN(){
    int l[100], rt[100], lc=0, rc=0, t=0, p=h, ds=200;
    for(int i=0;i<n;i++)
        (r[i]<h?l[lc++]:rt[rc++])=r[i];
    s(l,lc); s(rt,rc);

    printf("\nSeek Sequence: %d", p);
    if(d==2){
        for(int i=0;i<rc;i++) t+=abs(p-rt[i]), p=rt[i], printf(" -> %d", p);
        t+=abs(p-(ds-1)); p=ds-1;
        t+=abs(p-0); p=0; printf(" -> %d", p);
        for(int i=0;i<lc;i++) t+=abs(p-l[i]), p=l[i], printf(" -> %d", p);
    } else {
        for(int i=lc-1;i>=0;i--) t+=abs(p-l[i]), p=l[i], printf(" -> %d", p);
        t+=abs(p-0); p=0;
        t+=abs(p-(ds-1)); p=ds-1; printf(" -> %d", p);
        for(int i=rc-1;i>=0;i--) t+=abs(p-rt[i]), p=rt[i], printf(" -> %d", p);
    }
    printf("\nTotal Seek Time = %d\n", t);
}

int main(){
    printf("Enter number of requests: "); scanf("%d",&n);
    printf("Enter request sequence:\n");
    for(int i=0;i<n;i++) scanf("%d",&r[i]);
    printf("Enter initial head position: "); scanf("%d",&h);
    printf("Enter direction (1 = Left, 2 = Right): "); scanf("%d",&d);

    int c;
    while(1){
        printf("\n--- Disk Scheduling ---\n1. SSTF\n2. LOOK\n3. C-SCAN\n4. Exit\nEnter choice: ");
        scanf("%d",&c);
        if(c==4) break;
        if(c==1) SSTF();
        else if(c==2) LOOK();
        else if(c==3) CSCAN();
        else printf("Invalid choice!\n");
    }
}