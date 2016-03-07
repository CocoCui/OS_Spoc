# 最先匹配实现文档


**最先匹配：即分配n个字节，使用第一个可用的空间比n大的空闲块  **
实现的原理如下： 

* 空闲分区列表按地址顺序排序
* 分配时搜索一个合适的分区
* 释放时检测是否可以与临近的空闲分区合并

维护一个有序的列表，这个列表中存储了所有空闲的内存块的信息，在需要分配内存时，按顺序遍历该列表，并将第一个不小于他的内存块分配出去，如果这个内存块大小刚好等于需要分配的内存空间的大小，则直接将该内存块分配并将其对应的表项删除即可。如果这个内存块大于需要的分配的内存，则分配请求大小的内存，并将原空闲内存的起点设为分配内存的起点+分配的大小即可。在释放一块内存时，遍历空闲的内存块列表，将与被释放空间相邻的内存块从列表中删除，并将合并后的空间起点，大小信息重新加入列表即可。

测试样例： 

	malloc(100);  
	malloc(100);  
	malloc(100);   
	malloc(100);  
	malloc(600); 
	malloc(100); 
	free(100,100); 
	free(300,100); 
	free(200,100); 
	free(0,100); 

输出结果：  

	Begin from: 0
	Free Blocks:
	begin:100 size:924
	Begin from: 100
	Free Blocks:
	begin:200 size:824
	Begin from: 200
	Free Blocks:
	begin:300 size:724
	Begin from: 300
	Free Blocks:
	begin:400 size:624
	Begin from: 400
	Free Blocks:
	begin:1000 size:24
	Failed
	Free Blocks:
	begin:1000 size:24
	free 100 to 100
	Free Blocks:
	begin:100 size:100
	begin:1000 size:24
	free 300 to 100
	Free Blocks:
	begin:100 size:100
	begin:300 size:100
	begin:1000 size:24
	free 200 to 100
	merged with free memory block begin from 100, size: 100
	merged with free memory block begin from 300, size: 100
	Free Blocks:
	begin:100 size:300
	begin:1000 size:24
	free 0 to 100
	merged with free memory block begin from 100, size: 300
	Free Blocks:
	begin:0 size:400
	begin:1000 size:24
	
```在分配内存时，都是从低地值开始分配。释放的过程中，先释放了[100,200]和[300,400]两个内存块，当[200,300]这一块内存被释放后，该内存块与之前释放的内存合并成了[100,400]的空闲区域。
```

