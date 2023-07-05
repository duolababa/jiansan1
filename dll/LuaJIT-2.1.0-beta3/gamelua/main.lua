package.path="D:\dll2-无痕-线程-lua\dll\LuaJIT-2.1.0-beta3\gamelua"--GetPackagePatch();
local loadArr={"role","ui"}
for i=1,#loadArr
do 
	package.loaded[loadArr[i]]=nil;
	require(loadArr[i]);
end


