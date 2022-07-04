
<script>
    import Board from './board.svelte'

    export let name;
    export let data;

    let selectedSwitch = 0;

    const selectSwitch = (index) => {
        selectedSwitch = index;
    }

    const changeName = (e) => {
        if(e.which === 13) {
            const newName = e.target.innerText;
            if(data.layers[newName]) {
                e.target.innerText = name;
                e.target.blur();
                e.preventDefault();
                return;
            };
            data.layers[newName] = data.layers[name];
            delete data.layers[name];

            data.order[data.order.indexOf(name)] = newName;

            console.log(data)

            name = newName;
            e.target.blur();
            e.preventDefault();
            return;
        }
    }

</script>

<div id="panel">
    <div>
        <h1 contenteditable={true} on:keypress={changeName}>{name}</h1>
        
        <Board selectSwitch={selectSwitch} selectedSwitch={selectedSwitch}/>
    </div>
</div>

<style>
    h1 {
        color: var(--f_med);
        outline: none;
        padding-bottom: 3px;
    }

    h1:focus {
        padding-bottom: 0;
        border-bottom: 3px solid var(--f_med);
    }

    #panel {
        display: flex;
        width: 75%;
        height: 50%;
    }

    #panel div {
        margin: auto auto;
    }

</style>