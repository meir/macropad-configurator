
<script>
    import Dots from '../components/dots.svelte'

    export let data;
    export let selectLayer;

    let selected = 0;

    let drag = {
        mouseY: null,
        hoverIndex: null,
        dragIndex: null,
        distance: null,
    }

    function bc(b, c) {
        return b ? c : '';
    }

    function click(index) {
        selected = index;
        selectLayer(data.order[selected]);
    }

    $: {
        if(drag.hoverIndex !== null && drag.dragIndex !== null) {
            [data.order[drag.hoverIndex], data.order[drag.dragIndex]] = [data.order[drag.dragIndex], data.order[drag.hoverIndex]];
            drag.dragIndex = drag.hoverIndex;
            click(drag.dragIndex);
        }
    }
</script>

<div class="b_low">
    <ul>
        {#if drag.mouseY}
            <li 
                class={`f_low b_high selected ghost`}
                style={`top: ${drag.mouseY + drag.distance}px`}
            >
                {data.order[drag.dragIndex]}
            </li>
        {/if}
        {#each data.order as layer, index}
            <li 
                class={`f_low b_high ${bc(selected === index, 'selected')} ${bc(drag.dragIndex === index, 'hide')}`} on:click={(e) => click(index)}
                on:dragover={(e) => {
                    drag.hoverIndex = index;
                }}
            >
                <span 
                    class="drag"
                    draggable={true}
                    on:dragstart={(e) => {
                        click(index);
                        drag.mouseY = e.clientY;
                        drag.dragIndex = index;
                        // @ts-ignore
                        drag.distance = e.target.getBoundingClientRect().y - e.clientY;
                    }}
                    on:drag={(e) => {
                        drag.mouseY = e.clientY;
                    }}
                    on:dragend={(e) => {
                        drag.mouseY = null;
                        drag.hoverIndex = null;
                        drag.dragIndex = null;
                        drag.distance = null;
                    }}
                >
                    <Dots/>
                </span>
                <div>
                    {layer}
                </div>
            </li>
        {/each}
    </ul>
</div>

<style>
    div {
        display: flex;
        height: 100%;
        width: 25%;
    }
    ul {
        list-style: none;
        padding: 10px;
        margin: 0;
        width: 100%;
    }

    li {
        margin-bottom: .5rem;
        padding: 5px;
        border-radius: 3px;
        display: flex;
        opacity: 80%;
        cursor: pointer;
    }

    li div {
        display: flex;
        height: auto;
        justify-content: center;
        flex-direction: column;
        line-height: 1.5;
    }

    li:last-child {
        margin-bottom: 0;
    }

    li:hover {
        opacity: 100%;
    }

    li.selected {
        opacity: 100%;
    }

    .drag {
        cursor: grab;
        display: flex;
        padding: 4px;
        margin-right: 2px;
    }

    .hide {
        opacity: 0 !important;
    }

    .ghost {
        margin-bottom: 10px;
        pointer-events: none;
        z-index: 99;
        position: absolute;
        top: 0;
        left: 10px;
    }
</style>