# 自定义控件

+ 有可实现下拉功能
+ 含有QCheckBox勾选
+ 状态设置功能

2023年7月1日

<style>
    .scrolling-text {
        white-space: nowrap;
        overflow: hidden;
        animation: scroll-left 10s linear infinite;
    }

    @keyframes scroll-left {
        0% {
            transform: translateX(0%);
        }
        100% {
            transform: translateX(-100%);
        }
    }
</style>

<div class="scrolling-text">
    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris dapibus ultricies nibh, vel fermentum sapien sagittis sed. Nunc semper scelerisque lacus, a consequat nibh hendrerit a. Pellentesque facilisis posuere sapien, ac hendrerit dui maximus vel. In nec nisl vitae magna interdum feugiat. Fusce sed metus non ipsum ullamcorper fringilla. Sed efficitur cursus sapien, sed pulvinar massa gravida non. Quisque id libero auctor, consequat nisi ut, tempor lorem. Curabitur nec dolor eu lectus lobortis malesuada.
</div>
