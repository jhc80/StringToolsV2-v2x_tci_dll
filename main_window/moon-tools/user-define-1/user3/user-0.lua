App.ClearScreen();

local mf = new_memfile("Z:\\tmp\\123.gif");

local gif = XImageGIF.new();

gif:Decode(mf);
local n = gif:GetNumFrames();

local gif1 = XImageGIF.new();
gif1:SetFrame(n-1);
gif1:SetRetreiveAllFrames(true);
gif1:Decode(mf);
