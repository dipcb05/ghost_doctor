<?php

namespace App\Http\Controllers;
use Revolution\Google\Sheets\Facades\Sheets;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\View;

class DataController extends Controller
{
    public function index(){
        return view('welcome');
    }
    public function SensorData(){
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
    public function Control(){
        $sheets = Sheets::spreadsheet(config('sheets.post_spreadsheet_id'))
        ->sheetById(1136296805)
        ->all();
        foreach($sheets[0] as $index => $name ){
            $tasks[] = array(
                'task_name' => $name,
                'task_value' => $sheets[1][$index],
            );
         } 
        return view('controls', ['tasks' => $tasks]);
    }
    public function changeStatus(Request $request)
    {
        $sheets = Sheets::spreadsheet(config('sheets.post_spreadsheet_id'))
        ->sheetById(1136296805)
        ->all();
        $fan = $sheets[1][0];
        $drawer1 = $sheets[1][1];
        $drawer2 = $sheets[1][2];
        $fan_speed = $sheets[1][3];

        if($request->task_name == "fan")
         $fan = ($request->status == 1) ? "1" : "0";
        else if($request->task_name == "drawer1")
         $drawer1 = ($request->status == 1) ? "1" : "0";
        else if($request->task_name == "drawer2")
         $drawer2 = ($request->status == 1) ? "1" : "0";
        else if($request->task_name == "fan_speed") $fan_speed = $request->value;

        Sheets::spreadsheet(config('sheets.post_spreadsheet_id'))
          ->sheetById(1136296805)
          ->range('A2')
          ->update([[$fan,$drawer1,$drawer2,$fan_speed]]);
        return response()->json(['success'=>'Status change successfully.']);
    }
}