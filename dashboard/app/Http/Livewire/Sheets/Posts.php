<?php

namespace App\Http\Livewire\Sheets;
use Livewire\Component;
use Revolution\Google\Sheets\Facades\Sheets;

class Posts extends Component
{
    protected $listeners = ['postAdded' => 'render', 'getPostsProperty'];
    //, 'new' => '$refresh'
    public function getPostsProperty()
    {        
        $sheets = Sheets::spreadsheet(config('sheets.post_spreadsheet_id'))
                        ->sheetById(config('sheets.post_sheet_id'))
                        ->all();
        $data = $sheets[sizeof($sheets) - 1];    
        $posts[] = array(   
            'datetime'    => $data[0],   
            'humidity'    => $data[1],
            'temparature' => $data[2],
            );
        
        return $posts;
    }

    public function render()
    {
        return view('livewire.sheets.posts');
    }
}
