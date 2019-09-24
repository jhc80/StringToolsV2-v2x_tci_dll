--如何打印的函数--

function how_to_print(x,y,color)   
    App.ClearScreen();
    local r,g,b = rgb(color);
    printfnl("(%d,%d)  rgb(%d,%d,%d)  #%02x%02x%02x",
        x,y,
        r,g,b,
        r,g,b
    );
end
