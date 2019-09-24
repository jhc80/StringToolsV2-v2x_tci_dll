--拍照后延时时长，以豪秒为单位，最小为100--
delay = 500;

--最小相似度，如果低于这个值就认为是不同的
--就会进行拍照的动作
min_similarity = 0.8;

--比较两张图片不同的阀值--
threshold = 100;

--保存在哪一个文件夹下面
save_path = "z:\\tmp\\";

--激活哪一个设备--
active_device = 0;

--如何生成文件名--
function create_file_name(index)
    return string.format("photo-%04d.jpg",index);
end
