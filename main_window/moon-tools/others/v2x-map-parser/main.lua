require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

function _octet_string(str)
    return "octet_string:"..str;
end

function _bit_string(str)
    return "bit_string:"..str;
end

function _ia5_string(str)
    return "ia5_string:"..str;
end

if not exec_string(mem_text:CStr()) then
    return
end
if not messageFrame then return end

function dump_lane_point(point,refPos)
    local offsetLL = point.posOffset.offsetLL;
    local offsetV = point.posOffset.offsetV;

    local lat = refPos.lat;
    local lon = refPos.long;
    local alt = refPos.elevation;

    local off = nil;

    if offsetLL.present == 1 then
        off = offsetLL["position-LL1"];
    elseif offsetLL.present == 2 then
        off = offsetLL["position-LL2"];        
    elseif offsetLL.present == 3 then
        off = offsetLL["position-LL3"];        
    elseif offsetLL.present == 4 then
        off = offsetLL["position-LL4"];        
    elseif offsetLL.present == 5 then
        off = offsetLL["position-LL5"];        
    elseif offsetLL.present == 6 then
        off = offsetLL["position-LL6"];        
    elseif offsetLL.present == 7 then
        local ll = offsetLL["position-LatLon"];        
        lat = ll.lat;
        lon = ll.lon;
    end

    if off then
        lat = lat + off.lat;
        lon = lon + off.lon;
    end

    local v_off = nil;
    if offsetV then
        if offsetV.present == 1 then
            v_off = offsetV["offset1"];
        elseif offsetV.present == 2 then
            v_off = offsetV["offset2"];            
        elseif offsetV.present == 3 then
            v_off = offsetV["offset3"];            
        elseif offsetV.present == 4 then
            v_off = offsetV["offset4"];            
        elseif offsetV.present == 5 then
            v_off = offsetV["offset5"];            
        elseif offsetV.present == 6 then
            v_off = offsetV["offset6"];            
        elseif offsetV.present == 7 then
            local e = offsetV["elevation"];
            alt = e;
        end
    end

    if v_off then
        alt = alt + v_off;
    end

    printfnl("        %f,%f,%f",lat/10000000,lon/10000000,alt/10);
end

function dump_map_message_points_2017(messageFrame)
    if not messageFrame then return end
    if not messageFrame.mapFrame then return end
    if not messageFrame.mapFrame.nodes then return end
    
    local nodes = messageFrame.mapFrame.nodes;
    for _,node in ipairs(nodes) do
        printfnl("*node=%d",node.id.id);

        if node.inLinks then
            for _, inLink in ipairs(node.inLinks) do
                printfnl("  *upstreamNodeId=%d",inLink.upstreamNodeId.id);

                if inLink.lanes then

                    for _,lane in ipairs(inLink.lanes) do
                        printfnl("    *laneID=%d",lane.laneID);
                        for _,connectTo in ipairs(lane.connectsTo) do
                            printfnl("      *remoteIntersection=%d",connectTo.remoteIntersection.id);
                            printfnl("      *connectingLane=%d",connectTo.connectingLane.lane);
                            if connectTo.phaseId then
                                printfnl("      *phaseId=%d",connectTo.phaseId);
                            end
                        end

                        if lane.points then
                            printfnl("      *points=")
                            for _,point in ipairs(lane.points) do                                
                                dump_lane_point(point,node.refPos);
                            end
                        end
                    end
                end
            end
        end
    end
end


dump_map_message_points_2017(messageFrame);

