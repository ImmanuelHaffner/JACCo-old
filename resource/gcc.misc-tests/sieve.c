




char flags[8190 +1];

main()
{
 register int i, prime, k, count, iter;
 for (iter=1;iter<=100;iter++) {
  count=0;
  for (i=0;i<=8190;i++)
   flags[i]=1;
  for (i=0;i<=8190;i++) {
   if (flags[i]) {
    prime=i+i+3;
    for (k=i+prime;k<=8190;k+=prime)
     flags[k]=0;
    count++;
   }
  }
 }
 return 0;
}
