<x-guest-layout>
   <div class="grid-cols-3 sm:grid-cols-2 p-6">
       <div class="card">
        <div class="card-header">Patient Number</div>
        <ul class="nav">
        <li class="nav-item">
        <a class="nav-link active" aria-current="page" href="#">1</a>
        </li>
        @for ($i = 2; $i <= 15; $i++)
        <li class="nav-item"><a class="nav-link" href="#">{{ $i }}</a></li>
        @endfor
        </ul>
       <div class="card-footer">2nd Floor</div>
       </div>
    </div>
    <div class="grid-cols-3 sm:grid-cols-2 p-6">
            <livewire:sheets.posts></livewire:sheets.posts>
    </div>    
    <div class="grid-cols-3 sm:grid-cols-2 p-6">
            <div class="card">
             <div class="card-header">Patient Details</div>
             <div class="card-body">
             <h6 class="card-title"><b>Mr. John Doe</b></h6><br>
             <h7><b>Admitted in: </b>2nd Floor, 215 no. Bed</h7><br>
             <h7><b>Admission date: </b>20/03/2022</h7><br>
             <h7><b>Reason: </b>Demo Disease</h7><br>
             <h7><b>Emergency Patient Contact Number: </b>12345678</h7><br>
             <h7><b>Blood Group: </b>B+</h7><br>
             <p class="card-text">Demo disease description.<br>ksdnvjergjr bghjrb gherhb hrghergher bghrbghbrhgberhgbhrbg</p><br>
             </div>
             <div class="card-footer">Condition: Saturated</div>
           </div>
    </div>

</x-guest-layout>
