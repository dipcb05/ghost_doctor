<?php

namespace App\Http\Controllers;
use Revolution\Google\Sheets\Facades\Sheets;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\View;

class DataController extends Controller
{
    public function index()
    {
        return view('welcome');
    }
    public function SensorData()
    {
        $sheets = Sheets::spreadsheet(config('sheets.post_spreadsheet_id'))
                    ->sheetById(config('sheets.post_sheet_id'))
                    ->all();

        $posts = array();
        foreach ($sheets as $data) {
            $posts[] = array(   
                'datetime'    => $data[0],   
                'humidity'    => $data[1],
                'temparature' => $data[2],
                );
        }
        return view('layouts.data', ['posts' => $posts]);
    }
}