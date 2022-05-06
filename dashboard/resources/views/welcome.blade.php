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
        <div>
            <livewire:sheets.posts></livewire:sheets.posts>
        </div>
    </div>    
</x-guest-layout>
