<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\DataController;
/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return redirect()->route('dashboard');
});
Route::get('/dashboard', [DataController::class, 'index'])->name('dashboard');
Route::get('/alldatas', [DataController::class, 'SensorData'])->name('data');
Route::get('/control', [DataController::class, 'Control'])->name('control');
Route::get('/changeStatus', [DataController::class, 'changeStatus']);