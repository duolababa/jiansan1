 1 --类的声明，这里声明了类名还有属性，并且给出了属性的初始值
 2 role = {x=0,y=0}
 3 --设置元表的索引，想模拟类的话，这步操作很关键
 4 role.__index = role
 5 --构造方法，构造方法的名字是随便起的，习惯性命名为new()
 6 function role:new(x,y)
 7      local t = {}  --初始化t，如果没有这句，那么类所建立的对象如果有一个改变，其他对象都会改变
 8      setmetatable(t, role)  --将t的元表设定为Class
 9      t.x = x   --属性值初始化
10      t.y = y
11      return t  --返回自身
12 end
13 
14 --这里定义类的其他方法
15 function role:test()
16  print(self.x,self.y)
17 end
18 
19 function role:plus()
20  self.x = self.x + 1
21  self.y = self.y + 1
22 end



function role:getallrole()
	local pBA_LOGINROLE2 = cpp_GameDllBase + cpp_BA_LOGINROLE2;
	local pBeginAddr = R_P(pBA_LOGINROLE2);
	local nLen = R_I(pBA_LOGINROLE2 + 0x8);
	for i = 1, nLen
	do
	   	local pObj = R_PTR(pBeginAddr + (i-1) * 8);
		local pName = (char*)(pObj + 0x10);
		pName = utf8_to_string(pName);
		local c_name = CString(pName.c_str());
		local ID = R_DW(pObj + OFF_ITEMID);
		DebugPrintf(L"綫上 pObj:%I64X,name:%s ,id %d", pObj, c_name, ID);
	end
end
